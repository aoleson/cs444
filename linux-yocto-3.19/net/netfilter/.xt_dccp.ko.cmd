cmd_net/netfilter/xt_dccp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_dccp.ko net/netfilter/xt_dccp.o net/netfilter/xt_dccp.mod.o
