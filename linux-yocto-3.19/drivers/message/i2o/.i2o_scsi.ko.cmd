cmd_drivers/message/i2o/i2o_scsi.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o drivers/message/i2o/i2o_scsi.ko drivers/message/i2o/i2o_scsi.o drivers/message/i2o/i2o_scsi.mod.o
