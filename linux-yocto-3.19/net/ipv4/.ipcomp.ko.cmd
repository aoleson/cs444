cmd_net/ipv4/ipcomp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/ipv4/ipcomp.ko net/ipv4/ipcomp.o net/ipv4/ipcomp.mod.o
