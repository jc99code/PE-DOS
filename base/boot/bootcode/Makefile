
include $(BASEPATH)\include\make\sdktools.inc

BOOTCODE = bootcode

FAT_BOOTCODE = fat\$(BOOTCODE).bin

all: $(BOOTDISK)

.PHONY: all

$(FAT_BOOTCODE): fat\$(BOOTCODE).asm
	$(asm) -f bin -o $@ $<

$(BOOTDISK): $(FAT_BOOTCODE)
	$(dd) if=/dev/zero of=$@ bs=512 count=2880
	$(dd) if=$< of=$@ bs=512 seek=0 count=1
