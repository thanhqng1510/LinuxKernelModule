KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd`
	make -C $(KDIR) M=$(PWD) modules
	$(CC) test.c -o random
auto:
	make -C $(KDIR) M=`pwd`
	sudo insmod Random.ko
	make -C $(KDIR) M=$(PWD) modules
	$(CC) test.c -o random
	sudo ./random
	sudo rmmod Random
	make clean
clean:
	make -C $(KDIR) M=`pwd` clean
