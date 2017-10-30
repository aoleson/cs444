cmd_arch/x86/boot/compressed/cpuflags.o := i586-poky-linux-gcc -Wp,-MD,arch/x86/boot/compressed/.cpuflags.o.d  -nostdinc -isystem /scratch/opt/poky/1.8/sysroots/i686-pokysdk-linux/usr/bin/i586-poky-linux/../../lib/i586-poky-linux/gcc/i586-poky-linux/4.9.2/include -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__ -m32 -D__KERNEL__ -O2 -fno-strict-aliasing -fPIC -DDISABLE_BRANCH_PROFILING -march=i386 -mno-mmx -mno-sse -ffreestanding -fno-stack-protector    -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(cpuflags)"  -D"KBUILD_MODNAME=KBUILD_STR(cpuflags)" -c -o arch/x86/boot/compressed/cpuflags.o arch/x86/boot/compressed/cpuflags.c

source_arch/x86/boot/compressed/cpuflags.o := arch/x86/boot/compressed/cpuflags.c

deps_arch/x86/boot/compressed/cpuflags.o := \
    $(wildcard include/config/randomize/base.h) \

arch/x86/boot/compressed/cpuflags.o: $(deps_arch/x86/boot/compressed/cpuflags.o)

$(deps_arch/x86/boot/compressed/cpuflags.o):
