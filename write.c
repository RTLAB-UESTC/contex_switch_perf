#include<unistd.h> 	
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<time.h>

#define BUF_LEN 4// 268 
#define TIMES 300 
//67*4

static char *dev_name = "/dev/demodev";

unsigned long long timeNanos()
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    return (unsigned long long) tp.tv_sec * (1000ULL * 1000ULL * 1000ULL) + (unsigned long long) tp.tv_nsec;
}

int main(int argc,char *argv[])
{
	int fd;
	char mybuf[128];
	int nread,nwrite;
	int i;
	
	fd = open( dev_name , O_RDWR );
	if(fd == -1)
	{
		printf("open failed.\n");
		return EXIT_FAILURE;
	}
	
	char * buf = (char*)malloc(BUF_LEN);
	if (NULL == buf)
	{
		printf("malloc error\n");
		return EXIT_FAILURE;
	}
 	unsigned long long start,end,use;

	start = timeNanos();

	for (i=0; i < TIMES; i++ )
	{
		nwrite = write(fd, (const void*)buf, BUF_LEN);
		if (nwrite != BUF_LEN)
		{	
			printf ("write buf to driver failed,return val:%d \n", nwrite);
			return nwrite;
		}
	}

	end = timeNanos();
	
	use = ( end - start );// / TIMES;
		printf("each time write to kernel takes time:%3llu.%09llus\n", 
		(unsigned long long)use / 1000000000, 
		(unsigned long long)use % 1000000000);

	#if 0
	nwrite = write(fd, argv[1], strlen(argv[1]));
	if (nwrite != strlen (argv[1]))
	{	
		printf ("write buf to driver failed \n");
		return nwrite;
	}
	printf ("write data:[%s]-->successfully\n",argv[1]);
	#endif
	close(fd);
	
	return EXIT_SUCCESS;
}

















