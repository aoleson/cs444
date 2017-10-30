cmd_crypto/cast_common.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/cast_common.ko crypto/cast_common.o crypto/cast_common.mod.o
