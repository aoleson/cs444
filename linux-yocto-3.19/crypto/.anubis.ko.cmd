cmd_crypto/anubis.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/anubis.ko crypto/anubis.o crypto/anubis.mod.o
