#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include "/home/baptiste/linux-next/include/linux/kbd_kern.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nidzik gg <nidzik@student.42.fr>");
MODULE_DESCRIPTION("Hello World module");

static struct miscdevice my_dev;


static ssize_t my_write(struct file *file,
			const char __user *ubuf,
			size_t count,
			loff_t *ppos)
{

	if (strncmp(ubuf, "nidzik\n", 7 ) == 0)
	{
		printk("TRUE\n");	
		return 7;
	}
	else 
	{
		printk("FALSE\n");
		return EINVAL;
	}
}


static ssize_t my_read(struct file *file, char __user *buf, size_t size, loff_t * pos)
{
	int error_count = 0;
	char * name = "nidzik";
	
	if (!file || !buf || !pos)
		return (-EFAULT);	
	if (size < 6)
		return -EINVAL;
	else if (*pos >= 6)
		return 0;

	error_count = copy_to_user((void *)buf + *pos , name, 6);
	
	if (error_count)
		return(-EFAULT);
	*pos += size;
	
	return  (6);
}

static const struct file_operations mymisc_fops = {  
    	.read = my_read,
	.write = my_write  
};  

static int __init hello_init(void) {
	int retval;
	
	printk(KERN_INFO "Hello Wolrd!\n");
    	my_dev.minor = MISC_DYNAMIC_MINOR;
    	my_dev.name = "fortytwo";
    	my_dev.fops = &mymisc_fops;
    	retval = misc_register(&my_dev);
    	if (retval) return retval;
    	printk("my: got minor %i\n",my_dev.minor);
	return 0;
}

static void __exit hello_cleanup(void) {
	printk(KERN_INFO "Cleaning up module.\n");
	misc_deregister(&my_dev);
}

module_init(hello_init);
module_exit(hello_cleanup);

