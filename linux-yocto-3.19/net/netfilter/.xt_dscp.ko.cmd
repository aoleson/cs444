cmd_net/netfilter/xt_dscp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_dscp.ko net/netfilter/xt_dscp.o net/netfilter/xt_dscp.mod.o
