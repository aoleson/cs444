cmd_net/netfilter/xt_conntrack.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_conntrack.ko net/netfilter/xt_conntrack.o net/netfilter/xt_conntrack.mod.o
