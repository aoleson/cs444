cmd_drivers/input/built-in.o :=  ld -m elf_i386   -r -o drivers/input/built-in.o drivers/input/input-core.o drivers/input/mousedev.o drivers/input/evdev.o drivers/input/keyboard/built-in.o drivers/input/mouse/built-in.o drivers/input/tablet/built-in.o drivers/input/touchscreen/built-in.o 
