cmd_firmware/tigon/tg3_tso.bin.gen.o := i586-poky-linux-gcc -Wp,-MD,firmware/tigon/.tg3_tso.bin.gen.o.d  -nostdinc -isystem /scratch/opt/poky/1.8/sysroots/i686-pokysdk-linux/usr/bin/i586-poky-linux/../../lib/i586-poky-linux/gcc/i586-poky-linux/4.9.2/include -I./arch/x86/include -Iarch/x86/include/generated/uapi -Iarch/x86/include/generated  -Iinclude -I./arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I./include/uapi -Iinclude/generated/uapi -include ./include/linux/kconfig.h -D__KERNEL__  -D__ASSEMBLY__ -m32 -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1  -DCONFIG_AS_CRC32=1 -DCONFIG_AS_AVX=1 -DCONFIG_AS_AVX2=1  -Wa,-gdwarf-2          -c -o firmware/tigon/tg3_tso.bin.gen.o firmware/tigon/tg3_tso.bin.gen.S

source_firmware/tigon/tg3_tso.bin.gen.o := firmware/tigon/tg3_tso.bin.gen.S

deps_firmware/tigon/tg3_tso.bin.gen.o := \

firmware/tigon/tg3_tso.bin.gen.o: $(deps_firmware/tigon/tg3_tso.bin.gen.o)

$(deps_firmware/tigon/tg3_tso.bin.gen.o):
