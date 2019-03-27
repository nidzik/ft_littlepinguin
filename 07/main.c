#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/debugfs.h>
#include <linux/miscdevice.h>
//#include <linux/sched.h>
//#include <linux/fs.h>
#include "/home/baptiste/linux-next/include/linux/kbd_kern.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("nidzik gg <nidzik@student.42.fr>");
MODULE_DESCRIPTION("Debugfs  module");

static struct mutex g_mutex;
static struct dentry *my_entry;

static ssize_t my_write(struct file *file,
			const char __user *ubuf,
			size_t count,
			loff_t *ppos)
{
	char *name = "nidzik";
	if (!file || !ubuf || !ppos)
		return (-EFAULT);

	if (strncmp(ubuf, name, 7 ) == 0)
		return 6;
	else
		return (-EINVAL);
}


static ssize_t my_read(struct file *file, char __user *buf, size_t size, loff_t * pos)
{
	int error_count = 0;
	char * name = "nidzik";

	if (!file || !buf || !pos)
		return (-EFAULT);
	if (size < 6)
		return (-EINVAL);
	else if (*pos >= 6)
		return 0;

	error_count = copy_to_user((void *)buf , name, 6);

	if (error_count)
		return(-EFAULT);

	*pos += 6;
	return  (6);
}

static const struct file_operations mymisc_fops = {
    	.read = my_read,
	.write = my_write
};

static int __init hello_init(void) {
	printk(KERN_INFO "Init Debugfs!\n");
	mutex_init(&g_mutex);
	my_entry = debugfs_create_dir("t", NULL);
	debugfs_create_file("id", S_IROTH |  S_IWOTH | S_IXOTH, my_entry, NULL, &mymisc_fops ); 
	debugfs_create_u64("jiffies", S_IROTH | S_IXOTH | S_IWOTH , my_entry, (u64*)&jiffies); 
	debugfs_create_file("foo", S_IRUSR | S_IWUSR |   S_IWOTH , my_entry, NULL, &mymisc_fops ); 
	return 0;
}

static void __exit hello_cleanup(void) {
	debugfs_remove_recursive(my_entry);
	printk(KERN_INFO "Cleaning up module Debugfs.\n");
	mutex_destroy(&g_mutex);
}

module_init(hello_init);
module_exit(hello_cleanup);

