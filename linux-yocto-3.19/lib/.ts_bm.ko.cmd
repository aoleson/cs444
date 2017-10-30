cmd_lib/ts_bm.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o lib/ts_bm.ko lib/ts_bm.o lib/ts_bm.mod.o
