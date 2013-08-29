#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>


static char *dev_name = "/dev/demodev";

int main(int argc,char *argv[])
{
	int fd;
	char mybuf[128];
	char wbuf[128] = "I'm a driver test program";
	int nread,nwrite;
	
	fd = open( dev_name , O_RDWR );
	if(fd == -1){
		perror("");
		printf("open failed.\n");
		return EXIT_FAILURE;
	}
	
	nread = read(fd, mybuf, 50);
	if (nread != 50)
	{	
		printf ("write buf to driver failed \n");
		return nwrite;
	}
	printf ("read data: %s\n",mybuf);
	
	close(fd);
	
	return EXIT_SUCCESS;
}

















