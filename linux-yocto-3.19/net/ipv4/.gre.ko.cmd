cmd_net/ipv4/gre.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/ipv4/gre.ko net/ipv4/gre.o net/ipv4/gre.mod.o
