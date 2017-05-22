CONFIG_MODULE_SIG=n	#to avoid module verification failed warning in dmesg
ifneq ($(KERNELRELEASE),)
#Kbuild part
obj-m +=debug_fs.o

else
#Normal build part

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD modules
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean
endif
