cmd_drivers/misc/eeprom/eeprom_93cx6.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/misc/eeprom/eeprom_93cx6.ko drivers/misc/eeprom/eeprom_93cx6.o drivers/misc/eeprom/eeprom_93cx6.mod.o
