cmd_net/netfilter/xt_CT.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_CT.ko net/netfilter/xt_CT.o net/netfilter/xt_CT.mod.o
