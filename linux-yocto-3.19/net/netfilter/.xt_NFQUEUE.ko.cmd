cmd_net/netfilter/xt_NFQUEUE.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_NFQUEUE.ko net/netfilter/xt_NFQUEUE.o net/netfilter/xt_NFQUEUE.mod.o
