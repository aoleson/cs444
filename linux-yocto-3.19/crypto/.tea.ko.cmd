cmd_crypto/tea.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o crypto/tea.ko crypto/tea.o crypto/tea.mod.o
