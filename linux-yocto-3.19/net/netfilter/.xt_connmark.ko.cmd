cmd_net/netfilter/xt_connmark.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_connmark.ko net/netfilter/xt_connmark.o net/netfilter/xt_connmark.mod.o
