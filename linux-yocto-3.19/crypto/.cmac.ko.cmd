cmd_crypto/cmac.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/cmac.ko crypto/cmac.o crypto/cmac.mod.o
