cmd_crypto/twofish_generic.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/twofish_generic.ko crypto/twofish_generic.o crypto/twofish_generic.mod.o
