cmd_net/netfilter/xt_length.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_length.ko net/netfilter/xt_length.o net/netfilter/xt_length.mod.o
