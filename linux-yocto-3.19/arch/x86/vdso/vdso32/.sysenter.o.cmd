cmd_arch/x86/vdso/vdso32/sysenter.o := i586-poky-linux-gcc -Wp,-MD,arch/x86/vdso/vdso32/.sysenter.o.d  -nostdinc -isystem /scratch/opt/poky/1.8/sysroots/i686-pokysdk-linux/usr/bin/i586-poky-linux/../../lib/i586-poky-linux/gcc/i586-poky-linux/4.9.2/include -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__  -D__ASSEMBLY__ -m32 -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_CRC32=1 -DCONFIG_AS_AVX=1 -DCONFIG_AS_AVX2=1 -Wa,-gdwarf-2         -c -o arch/x86/vdso/vdso32/sysenter.o arch/x86/vdso/vdso32/sysenter.S

source_arch/x86/vdso/vdso32/sysenter.o := arch/x86/vdso/vdso32/sysenter.S

deps_arch/x86/vdso/vdso32/sysenter.o := \
  arch/x86/vdso/vdso32/sigreturn.S \
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
  arch/x86/include/generated/uapi/asm/unistd_32.h \
  arch/x86/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \

arch/x86/vdso/vdso32/sysenter.o: $(deps_arch/x86/vdso/vdso32/sysenter.o)

$(deps_arch/x86/vdso/vdso32/sysenter.o):
