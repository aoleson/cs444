cmd_fs/nfsd/nfsd.ko := i586-poky-linux-ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o fs/nfsd/nfsd.ko fs/nfsd/nfsd.o fs/nfsd/nfsd.mod.o
