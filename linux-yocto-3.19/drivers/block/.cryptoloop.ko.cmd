cmd_drivers/block/cryptoloop.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/block/cryptoloop.ko drivers/block/cryptoloop.o drivers/block/cryptoloop.mod.o
