cmd_net/sched/sch_netem.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/sched/sch_netem.ko net/sched/sch_netem.o net/sched/sch_netem.mod.o
