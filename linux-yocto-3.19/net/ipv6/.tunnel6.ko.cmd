cmd_net/ipv6/tunnel6.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/ipv6/tunnel6.ko net/ipv6/tunnel6.o net/ipv6/tunnel6.mod.o
