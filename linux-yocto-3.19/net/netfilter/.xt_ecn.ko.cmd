cmd_net/netfilter/xt_ecn.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_ecn.ko net/netfilter/xt_ecn.o net/netfilter/xt_ecn.mod.o
