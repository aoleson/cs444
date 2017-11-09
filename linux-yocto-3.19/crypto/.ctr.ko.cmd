cmd_crypto/ctr.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/ctr.ko crypto/ctr.o crypto/ctr.mod.o
