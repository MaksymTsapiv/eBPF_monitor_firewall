
import netifaces
import subprocess
import os
import sys


project_dir = os.path.realpath(os.path.dirname(__file__))
os.chdir(os.path.join(project_dir, "monitorBX"))


interfaces = [i for i in range(2, len(netifaces.interfaces()[1:]) + 2)]
str_interfaces = ""
for elm in interfaces:
    str_interfaces += f"{elm} "

not_bannable_ip = ["0.0.0.0", "127.0.0.1", "127.0.0", "192.168", "10.0.1.1", "10.10.1.1"]

cmd = [f"sudo {os.path.join(project_dir, 'monitorBX', 'monitorBX')} {' '.join(str(i) for i in interfaces)}"]


ips_to_ban = []

def execute(cmd):
    popen = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    for line in popen.stdout: 
        line = line.decode().strip()
        if "Anomaly ip:" in line:
            ip = line.split(": ")[-1][:-1]
            flag_to_ban = True
            for no_ban in not_bannable_ip:
                if (no_ban in ip) or (ip in ips_to_ban):
                    flag_to_ban = False
                    break
            
            if flag_to_ban:
                while True:
                    to_ban = input(f"Do you want to ban ip {ip}? y\\n: ")
                    if to_ban == "y":
                        to_ban = True
                        break
                    elif to_ban == "n":
                        to_ban = False
                        break
                    else:
                        print("Wrong input, please try again")


            if flag_to_ban and to_ban:
                ips_to_ban.append(ip)
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        print(popen.stderr.read(), file=sys.stderr)
        raise subprocess.CalledProcessError(return_code, cmd)


execute(cmd)


