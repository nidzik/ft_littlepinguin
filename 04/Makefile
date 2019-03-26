
obj-m += usb_plug.o
#CFLAGS_usb_plug.o := -DDEBUG
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo cp usb_plug.ko /lib/modules/$(shell uname -r)/
	sudo depmod -av

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
