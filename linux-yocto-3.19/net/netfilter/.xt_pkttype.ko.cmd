cmd_net/netfilter/xt_pkttype.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_pkttype.ko net/netfilter/xt_pkttype.o net/netfilter/xt_pkttype.mod.o
