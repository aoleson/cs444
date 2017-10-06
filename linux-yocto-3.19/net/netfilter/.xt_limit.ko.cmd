cmd_net/netfilter/xt_limit.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_limit.ko net/netfilter/xt_limit.o net/netfilter/xt_limit.mod.o
