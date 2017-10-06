cmd_net/netfilter/xt_hashlimit.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_hashlimit.ko net/netfilter/xt_hashlimit.o net/netfilter/xt_hashlimit.mod.o
