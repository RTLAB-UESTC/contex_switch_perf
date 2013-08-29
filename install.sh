#!/bin/sh
	sudo insmod demo_drive.ko
	sudo mknod  /dev/demodev c 240 0
