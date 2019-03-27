
obj-m += main.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo insmod main.ko
	sudo ls -l /sys/kernel/debug/
	sudo ls -l /sys/kernel/debug/id
	cat /sys/kernel/debug/id11
	echo -ne nidzik > /sys/kernel/debug/id11
	sudo rmmod main
