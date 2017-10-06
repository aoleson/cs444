cmd_net/sctp/sctp.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/sctp/sctp.ko net/sctp/sctp.o net/sctp/sctp.mod.o
