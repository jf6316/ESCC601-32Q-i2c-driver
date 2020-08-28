KERNELDIR= /home/user/ONL/20200824/OpenNetworkLinux/packages/base/amd64/kernels/kernel-4.9-lts-x86-64-all/builds/jessie/linux-4.9.75

PWD:=$(shell pwd)
INSTALLDIR=$(PWD)
CC=gcc

obj-m += x86-64-cameo-escc601-32q.o
x86-64-cameo-escc601-32q-objs := x86-64-cameo-escc601-32q-common.o x86-64-cameo-escc601-32q-sys.o \
x86-64-cameo-escc601-32q-led.o x86-64-cameo-escc601-32q-fan.o x86-64-cameo-escc601-32q-power.o \
x86-64-cameo-escc601-32q-thermal.o x86-64-cameo-escc601-32q-qsfp.o

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
clean:     
	rm -rf *.o *.ko *.mod.c *.markers *.order *.symvers
.PHONY:modules clean