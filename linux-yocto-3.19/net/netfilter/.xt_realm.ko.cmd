cmd_net/netfilter/xt_realm.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_realm.ko net/netfilter/xt_realm.o net/netfilter/xt_realm.mod.o
