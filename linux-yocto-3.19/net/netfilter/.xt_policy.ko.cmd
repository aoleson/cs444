cmd_net/netfilter/xt_policy.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_policy.ko net/netfilter/xt_policy.o net/netfilter/xt_policy.mod.o
