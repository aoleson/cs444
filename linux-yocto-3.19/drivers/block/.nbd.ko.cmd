cmd_drivers/block/nbd.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/block/nbd.ko drivers/block/nbd.o drivers/block/nbd.mod.o
