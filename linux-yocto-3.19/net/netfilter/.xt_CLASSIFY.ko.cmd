cmd_net/netfilter/xt_CLASSIFY.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_CLASSIFY.ko net/netfilter/xt_CLASSIFY.o net/netfilter/xt_CLASSIFY.mod.o
