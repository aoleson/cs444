cmd_net/netfilter/nf_nat.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/nf_nat.ko net/netfilter/nf_nat.o net/netfilter/nf_nat.mod.o
