cmd_crypto/blowfish_common.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/blowfish_common.ko crypto/blowfish_common.o crypto/blowfish_common.mod.o
