cmd_crypto/twofish_common.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/twofish_common.ko crypto/twofish_common.o crypto/twofish_common.mod.o
