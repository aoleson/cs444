cmd_net/netfilter/nfnetlink_log.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/nfnetlink_log.ko net/netfilter/nfnetlink_log.o net/netfilter/nfnetlink_log.mod.o
