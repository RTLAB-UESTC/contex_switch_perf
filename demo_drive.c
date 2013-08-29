#include <linux/module.h>
//#include <linux/config.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/moduleparam.h>

#define SUCCESS 0
#define DEVICE_NAME "demodev" /* Dev name as it appears in /proc/devices */
#define BUF_LEN 2981 
//80 /* Max length of the message from the device */


static int Major = 240; /* Major number assigned to our device driver */
static int Device_Open = 0; /* Is device open? Used to prevent multiple */

static char msg[BUF_LEN]; /* The msg the device will give when asked */


static int device_open(struct inode *inode, struct file *file)
{
	if (Device_Open) 
	{
		return -EBUSY;
	}
	
	Device_Open++;
	printk("<1>device_open call\n");
	return SUCCESS;
}


static int device_release(struct inode *inode, struct file *file)
{
	Device_Open --; /* We're now ready for our next caller */
	
	printk("<1>device_release call\n");

	return 0;
}

static ssize_t device_read(struct file *filp,
			   char *buffer, /* The buffer to fill with data */
	                   size_t length, /* The length of the buffer */
			    loff_t *offset) /* Our offset in the file */
{
	int bytes_read = 0;
	if (length < BUF_LEN)
	{
		copy_to_user(buffer, msg, length);
		return length;
	}
	else
	{
		copy_to_user(buffer, msg, BUF_LEN);
		return BUF_LEN;
	}
}

static ssize_t device_write(struct file *filp,
							const char *buff,
							size_t len,
							loff_t *off)
{
//	memset (msg, 'a', BUF_LEN);
	if (BUF_LEN >= len)
	{	
	//	copy_from_user(msg, buff, len);
		return len;
	}
	else
	{
		printk ("Support maximum length = %d\n", BUF_LEN);
		return -EINVAL;
	}
}

static struct file_operations fops = {
	    .read    = device_read, 
		.write   = device_write,
		.open    = device_open,
		.release = device_release
};

static int __init testmod_init(void)
{
	int ret = register_chrdev(Major, DEVICE_NAME, &fops);
	
	if (ret < 0) 
	{
		printk ("Registering the character device failed with %d\n", ret);
		return ret;
	}
	
	printk("'create driver file: mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	
	memset (msg, 0x0, 80);	

	return 0;
}


static void __exit testmod_exit(void)
{
	/* Unregister the device */
	unregister_chrdev(Major, DEVICE_NAME);//取消注册 取消了后模块可以unload
} 

module_init(testmod_init);
module_exit(testmod_exit);

