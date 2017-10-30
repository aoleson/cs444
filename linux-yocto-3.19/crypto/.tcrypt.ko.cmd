cmd_crypto/tcrypt.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/tcrypt.ko crypto/tcrypt.o crypto/tcrypt.mod.o
