cmd_net/netfilter/xt_multiport.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_multiport.ko net/netfilter/xt_multiport.o net/netfilter/xt_multiport.mod.o
