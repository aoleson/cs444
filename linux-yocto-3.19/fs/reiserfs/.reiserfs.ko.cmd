cmd_fs/reiserfs/reiserfs.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o fs/reiserfs/reiserfs.ko fs/reiserfs/reiserfs.o fs/reiserfs/reiserfs.mod.o
