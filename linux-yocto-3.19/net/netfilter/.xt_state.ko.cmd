cmd_net/netfilter/xt_state.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_state.ko net/netfilter/xt_state.o net/netfilter/xt_state.mod.o
