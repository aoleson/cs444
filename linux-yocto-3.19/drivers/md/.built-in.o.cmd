cmd_drivers/md/built-in.o :=  i586-poky-linux-ld -m elf_i386   -r -o drivers/md/built-in.o drivers/md/linear.o drivers/md/raid0.o drivers/md/raid1.o drivers/md/raid10.o drivers/md/multipath.o drivers/md/faulty.o drivers/md/md-mod.o drivers/md/dm-mod.o drivers/md/dm-builtin.o drivers/md/dm-bufio.o drivers/md/dm-crypt.o drivers/md/dm-snapshot.o drivers/md/dm-mirror.o drivers/md/dm-log.o drivers/md/dm-region-hash.o drivers/md/dm-zero.o 
