cmd_drivers/video/fbdev/uvesafb.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/video/fbdev/uvesafb.ko drivers/video/fbdev/uvesafb.o drivers/video/fbdev/uvesafb.mod.o
