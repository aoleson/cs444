cmd_drivers/block/floppy.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/block/floppy.ko drivers/block/floppy.o drivers/block/floppy.mod.o
