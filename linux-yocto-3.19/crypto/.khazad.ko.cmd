cmd_crypto/khazad.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/khazad.ko crypto/khazad.o crypto/khazad.mod.o
