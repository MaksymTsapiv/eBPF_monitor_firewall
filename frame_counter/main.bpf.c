#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

char LICENSE[] SEC("license") = "GPL";

struct {
    __uint(type, BPF_MAP_TYPE_HASH);
    __uint(max_entries, 4);
    __type(key, __u32);
    __type(value, char[24]);
} frame_map SEC(".maps");

int bpf_prog(void *ctx) {
    struct __sk_buff *skb = ctx;

    const char fmt_str[] = "len: %d, ifindex: %d\n";

    __u32 ingress_if_index = skb->ingress_ifindex;

    bpf_trace_printk(fmt_str, sizeof(fmt_str), skb->len, ingress_if_index);

    unsigned char packet[24];
    for (int i = 0; i < 24; ++i) {
        packet[i] = '\0';
    }
    long read = bpf_skb_load_bytes(skb, 0, packet, 24);

    if (!read) {
        __u32 key = 0;
        long err = bpf_map_update_elem(&frame_map, &key, packet, BPF_ANY);
        if (err) {
            char fmt[] = "error";
            bpf_trace_printk(fmt, sizeof(fmt));
        }
    }

    return 0;
}