#include <linux/bpf.h>
#include <bpf.h>
#include <libbpf.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <unistd.h>

void print_table(int ip, int arp, int other) {
    char start_buf[1000];
    char *buf = start_buf;

    buf += sprintf(buf, "\n\n\n\n");
    buf += sprintf(buf, "-------------------------\n");
    buf += sprintf(buf, "| %-21s |\n", "Number of frames");
    buf += sprintf(buf, "-------------------------\n");
    buf += sprintf(buf, "| %-5s | %-5s | %-5s |\n", "IP", "ARP", "OTHER");
    buf += sprintf(buf, "-------------------------\n");
    buf += sprintf(buf, "| %-5d | %-5d | %-5d |\n", ip, arp, other);
    sprintf(buf, "-------------------------\n");
    printf(start_buf);
    fflush(stdout);
}

int main() {
    struct bpf_object* obj = bpf_object__open_file("main.bpf.o", NULL); //TODO: should I free it? I think no
    if (!obj) {
        printf("failed to open bpf object file.\n");
        return EXIT_FAILURE;
    }

    struct bpf_program *prg = bpf_object__find_program_by_name(obj, "bpf_prog");
    if (!prg) {
        printf("failed to find program in bpf object file.\n");
        return EXIT_FAILURE;
    }

    int status = bpf_program__set_type(prg, BPF_PROG_TYPE_SOCKET_FILTER);
    if (status) {
        printf("failed to set type of bpf program. %d\n", status);
        return EXIT_FAILURE;
    }

    struct bpf_map *frame_map = bpf_object__find_map_by_name(obj, "frame_map");

    if (!frame_map) {
        printf("failed to find map by name\n");
        return EXIT_FAILURE;
    }


    bpf_object__load(obj);

    int sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock_fd < 0) {
        printf("error in socket\n");
        return EXIT_FAILURE;
    }

    int prog_fd = bpf_program__fd(prg);
    setsockopt(sock_fd, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd,
               sizeof(prog_fd));

    int no_ip = 0, no_arp = 0, no_other = 0;

    while (true) {
        __u32 key = 0;
        unsigned char value[24];
        int err = bpf_map__lookup_and_delete_elem(frame_map, &key, 4, value, 24, BPF_ANY);
        if (!err) {
            if (value[12] == 0x08 && value[13] == 0x00) {
                ++no_ip;
            } else if (value[12] == 0x08 && value[13] == 0x06) {
                ++no_arp;
            } else {
                ++no_other;
            }
            print_table(no_ip, no_arp, no_other);
        }
    }


//    sock = open_raw_sock("lo");
//
//    assert(setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd,
//                      sizeof(prog_fd)) == 0);
//
//    for (;;) {
//        key = IPPROTO_TCP;
//        assert(bpf_lookup_elem(map_fd, &key, &tcp_cnt) == 0);
//        key = IPPROTO_UDP;
//        assert(bpf_lookup_elem(map_fd, &key, &udp_cnt) == 0);
//        printf("TCP %lld UDP %lld packets\n", tcp_cnt, udp_cnt);
//        sleep(1);
//    }

    return 0;
}
