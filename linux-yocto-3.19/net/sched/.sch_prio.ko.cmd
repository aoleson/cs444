cmd_net/sched/sch_prio.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/sched/sch_prio.ko net/sched/sch_prio.o net/sched/sch_prio.mod.o
