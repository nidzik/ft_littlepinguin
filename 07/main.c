#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/debugfs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nidzik gg <nidzik@student.42.fr>");
MODULE_DESCRIPTION("Debugfs  module");

static struct dentry *my_entry;

static int __init hello_init(void) {
	printk(KERN_INFO "Init Debugfs!\n");
	my_entry = debugfs_create_dir("test", NULL);
	return 0;
}

static void __exit hello_cleanup(void) {
	debugfs_remove(my_entry);
	printk(KERN_INFO "Cleaning up module Debugfs.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

