cmd_lib/ts_fsm.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o lib/ts_fsm.ko lib/ts_fsm.o lib/ts_fsm.mod.o
