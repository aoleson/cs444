cmd_fs/fuse/cuse.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o fs/fuse/cuse.ko fs/fuse/cuse.o fs/fuse/cuse.mod.o
