cmd_drivers/net/dummy.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/net/dummy.ko drivers/net/dummy.o drivers/net/dummy.mod.o
