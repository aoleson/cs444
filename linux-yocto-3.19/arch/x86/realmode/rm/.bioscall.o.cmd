cmd_arch/x86/realmode/rm/bioscall.o := gcc -Wp,-MD,arch/x86/realmode/rm/.bioscall.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__  -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h  -m32 -Wa,./arch/x86/boot/code16gcc.h -g -Os -D__KERNEL__ -DDISABLE_BRANCH_PROFILING -Wall -Wstrict-prototypes -march=i386 -mregparm=3 -fno-strict-aliasing -fomit-frame-pointer -fno-pic -mno-mmx -mno-sse  -ffreestanding  -fno-stack-protector  -D_SETUP -D_WAKEUP -I./arch/x86/boot -D__ASSEMBLY__          -c -o arch/x86/realmode/rm/bioscall.o arch/x86/realmode/rm/bioscall.S

source_arch/x86/realmode/rm/bioscall.o := arch/x86/realmode/rm/bioscall.S

deps_arch/x86/realmode/rm/bioscall.o := \
  arch/x86/realmode/rm/../../boot/bioscall.S \

arch/x86/realmode/rm/bioscall.o: $(deps_arch/x86/realmode/rm/bioscall.o)

$(deps_arch/x86/realmode/rm/bioscall.o):
