cmd_drivers/net/ethernet/realtek/r8169.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/net/ethernet/realtek/r8169.ko drivers/net/ethernet/realtek/r8169.o drivers/net/ethernet/realtek/r8169.mod.o
