cmd_arch/x86/realmode/rm/copy.o := i586-poky-linux-gcc -Wp,-MD,arch/x86/realmode/rm/.copy.o.d  -nostdinc -isystem /scratch/opt/poky/1.8/sysroots/i686-pokysdk-linux/usr/bin/i586-poky-linux/../../lib/i586-poky-linux/gcc/i586-poky-linux/4.9.2/include -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__  -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h  -m16 -g -Os -D__KERNEL__ -DDISABLE_BRANCH_PROFILING -Wall -Wstrict-prototypes -march=i386 -mregparm=3 -fno-strict-aliasing -fomit-frame-pointer -fno-pic -mno-mmx -mno-sse  -ffreestanding  -fno-stack-protector  -mpreferred-stack-boundary=2 -D_SETUP -D_WAKEUP -I./arch/x86/boot -D__ASSEMBLY__          -c -o arch/x86/realmode/rm/copy.o arch/x86/realmode/rm/copy.S

source_arch/x86/realmode/rm/copy.o := arch/x86/realmode/rm/copy.S

deps_arch/x86/realmode/rm/copy.o := \
  arch/x86/realmode/rm/../../boot/copy.S \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/64bit.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/32.h) \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/x86/alignment/16.h) \

arch/x86/realmode/rm/copy.o: $(deps_arch/x86/realmode/rm/copy.o)

$(deps_arch/x86/realmode/rm/copy.o):
