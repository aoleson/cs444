cmd_crypto/tcrypt.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/tcrypt.ko crypto/tcrypt.o crypto/tcrypt.mod.o
