cmd_drivers/char/lp.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/char/lp.ko drivers/char/lp.o drivers/char/lp.mod.o
