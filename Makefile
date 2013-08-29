obj-m := demo_drive.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	gcc -o write write.c -lrt
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm write -f
	rm read -f
