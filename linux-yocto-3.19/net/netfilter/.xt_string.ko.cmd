cmd_net/netfilter/xt_string.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_string.ko net/netfilter/xt_string.o net/netfilter/xt_string.mod.o
