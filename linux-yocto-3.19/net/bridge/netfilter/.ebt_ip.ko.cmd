cmd_net/bridge/netfilter/ebt_ip.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/bridge/netfilter/ebt_ip.ko net/bridge/netfilter/ebt_ip.o net/bridge/netfilter/ebt_ip.mod.o
