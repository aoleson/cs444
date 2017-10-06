cmd_net/key/af_key.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/key/af_key.ko net/key/af_key.o net/key/af_key.mod.o
