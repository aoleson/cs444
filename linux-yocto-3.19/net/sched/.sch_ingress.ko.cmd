cmd_net/sched/sch_ingress.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o net/sched/sch_ingress.ko net/sched/sch_ingress.o net/sched/sch_ingress.mod.o
