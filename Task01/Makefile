ifneq ($(KERNELRELEASE),)
#Kbuild part
obj-m +=task01.o

else
#Normal build part

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD modules
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
