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
	char *name = "nidzik\0";

	if (!file || !ubuf || !ppos)
		return (-EFAULT);

	if (strncmp(ubuf, name, 7 ) == 0)
		return 7;
	else 
		return (-EINVAL);
}


static ssize_t my_read(struct file *file, char __user *buf, size_t size, loff_t * pos)
{
	int error_count = 0;
	char * name = "nidzik\0";
	
	if (!file || !buf || !pos)
		return (-EFAULT);	
	if (size < 7)
		return (-EINVAL);
	else if (*pos >= 7)
		return 0;

	error_count = copy_to_user((void *)buf + *pos , name, 7);
	
	if (error_count)
		return(-EFAULT);
	*pos += 7;
	
	return  (7);
}

static const struct file_operations mymisc_fops = {  
    	.read = my_read,
	.write = my_write  
};  

static int __init hello_init(void) {
	int retval;
	
	printk(KERN_INFO "Init module misc!\n");
    	my_dev.minor = MISC_DYNAMIC_MINOR;
    	my_dev.name = "fortytwo";
    	my_dev.fops = &mymisc_fops;
    	retval = misc_register(&my_dev);
    	if (retval) return retval;
    	printk("my_misc: got minor %i\n",my_dev.minor);
	return 0;
}

static void __exit hello_cleanup(void) {
	printk(KERN_INFO "Cleaning up module misc.\n");
	misc_deregister(&my_dev);
}

module_init(hello_init);
module_exit(hello_cleanup);

