cmd_drivers/ide/built-in.o :=  ld -m elf_i386   -r -o drivers/ide/built-in.o drivers/ide/ide-core.o drivers/ide/piix.o drivers/ide/ide-scan-pci.o drivers/ide/ide-gd_mod.o drivers/ide/ide-cd_mod.o 
