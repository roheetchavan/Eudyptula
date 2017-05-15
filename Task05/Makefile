CONFIG_MODULE_SIG=n

ifneq ($(KERNELRELEASE),)
#Kbuild part
obj-m +=usb_driver.o

else
#Normal build part

KDIR ?= /lib/modules/`uname -r`/build

all:
	$(MAKE) -C $(KDIR) M=$$PWD modules

clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
