cmd_fs/minix/minix.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o fs/minix/minix.ko fs/minix/minix.o fs/minix/minix.mod.o
