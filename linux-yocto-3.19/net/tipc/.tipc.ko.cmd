cmd_net/tipc/tipc.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/tipc/tipc.ko net/tipc/tipc.o net/tipc/tipc.mod.o
