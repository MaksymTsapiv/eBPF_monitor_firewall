# monitor-firewall

## Prerequisites

- glibc
- virtualenv (install it via pip)
- libbpf (version 0.5)

## Compilation

Run the following commands in the `monitor_firewall` directory:

1. Compile monitorBX:
```bash
$ cd monitorBX
$ sudo make
$ cd ..
```

2. Setup virtual environment:
```
$ cd Heimdallr-project
$ virtualenv .venv
$ source .venv/bin/activate
$ pip install -r requirements.txt
$ cd ..
```


## Usage

Run the following in the `monitor_firewall` directory:
```
$ python3 listener.py
```
