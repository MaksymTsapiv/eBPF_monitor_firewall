for iface in $(ifconfig | cut -d ' ' -f1| tr ':' '\n' | awk NF); do 
    sudo ip link set dev $iface xdp off
done
