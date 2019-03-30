
obj-m += usb_plug.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo cp usb_plug.ko /lib/modules/$(shell uname -r)/

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
