cmd_net/ipv6/netfilter/ip6t_rt.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/ipv6/netfilter/ip6t_rt.ko net/ipv6/netfilter/ip6t_rt.o net/ipv6/netfilter/ip6t_rt.mod.o
