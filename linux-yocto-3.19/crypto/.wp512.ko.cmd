cmd_crypto/wp512.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/wp512.ko crypto/wp512.o crypto/wp512.mod.o
