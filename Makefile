# Makefile
ifneq ($(KERNELRELEASE),)
    # kbuild part of makefile
    obj-m := ruth.o
else
    # normal makefile
    KDIR ?= /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif
