KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd`
auto:
	make -C $(KDIR) M=`pwd`
	sudo insmod Random.ko
	sudo cat /dev/Random
	sudo rmmod Random
	make clean
clean:
	make -C $(KDIR) M=`pwd` clean
