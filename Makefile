

DD = C:\Users\HeatS\Desktop\dd-0.5\dd.exe

IMAGE_FILENAME = bootdisk.img
IMAGE = $(BASEPATH)\$(IMAGE_FILENAME)

all: build-SYSTEM-sources build-SYSTEM-image

build-SYSTEM-sources:
	$(MAKE) -C lib
	$(MAKE) -C public
	$(MAKE) -C sdk
	$(MAKE) -C base

build-SYSTEM-image: $(IMAGE)

$(IMAGE):
	$(DD) if=/dev/zero of=$@ bs=512 count=2880
	
.PHONY: all
.PHONY: build-SYSTEM-sources build-SYSTEM-image
