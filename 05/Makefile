
obj-m += misc_char_driver.o 

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo insmod misc_char_driver.ko
	ls /dev/fortytwo -l
	sudo cat /dev/fortytwo
	sudo rmmod  misc_char_driver.ko
