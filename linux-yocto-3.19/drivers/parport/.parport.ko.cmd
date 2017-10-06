cmd_drivers/parport/parport.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/parport/parport.ko drivers/parport/parport.o drivers/parport/parport.mod.o
