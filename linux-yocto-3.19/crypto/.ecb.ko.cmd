cmd_crypto/ecb.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/ecb.ko crypto/ecb.o crypto/ecb.mod.o
