cmd_net/netfilter/nf_conntrack.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/netfilter/nf_conntrack.ko net/netfilter/nf_conntrack.o net/netfilter/nf_conntrack.mod.o
