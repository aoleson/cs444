cmd_net/netfilter/xt_statistic.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/xt_statistic.ko net/netfilter/xt_statistic.o net/netfilter/xt_statistic.mod.o
