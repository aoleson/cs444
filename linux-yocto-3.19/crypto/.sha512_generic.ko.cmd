cmd_crypto/sha512_generic.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/sha512_generic.ko crypto/sha512_generic.o crypto/sha512_generic.mod.o
