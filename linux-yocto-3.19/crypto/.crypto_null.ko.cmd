cmd_crypto/crypto_null.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/crypto_null.ko crypto/crypto_null.o crypto/crypto_null.mod.o
