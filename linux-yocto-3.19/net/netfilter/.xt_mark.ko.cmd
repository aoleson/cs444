cmd_net/netfilter/xt_mark.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_mark.ko net/netfilter/xt_mark.o net/netfilter/xt_mark.mod.o
