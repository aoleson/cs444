cmd_crypto/deflate.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/deflate.ko crypto/deflate.o crypto/deflate.mod.o
