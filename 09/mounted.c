// SPDX-License-Identifier: GPL-2.0+
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/nsproxy.h>
#include <linux/fs_struct.h>
#include <linux/kbd_kern.h>
#include <linux/fs.h>
#include <../fs/mount.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nidzik");
MODULE_DESCRIPTION("List mounted devices module.");


ssize_t my_read(struct file *file, char *buf, size_t count, loff_t *pos)
{
	struct dentry *curdentry;
	struct mnt_namespace *ns = current->nsproxy->mnt_ns ; 
	char str[256] = {0};
	char tmp[256] = {0}; 
	int error_count, len; 
	char *path;	

	len = 42;
	if (!file || !buf || !pos)
		return -EFAULT;
	if (*pos >= len-1)
		return 0 ;
	
	strncat(str, ns->root->mnt_devname, 4);
	strcat(str, "\t");
	strcat(str, current->fs->root.mnt->mnt_root->d_name.name);
	strcat(str, "\n");

	list_for_each_entry(curdentry,\
			&current->fs->root.mnt->mnt_root->d_subdirs, d_child)
	{
		if (curdentry->d_flags & DCACHE_MOUNTED)
		{
			path = dentry_path_raw(curdentry, tmp, sizeof(tmp));
			strcat(str, curdentry->d_name.name);
			strcat(str, "\t");
			strcat(str, path);
			strcat(str, "\n");
		}
	}
	len = strlen(str);
	error_count = copy_to_user((void *)buf ,str ,len);
	if (error_count)
		return(-EFAULT);
	*pos+= strlen(str);

	return (strlen(str));
}

struct file_operations proc_fops = {
	.owner = THIS_MODULE,
	.read = my_read
};


int __init mymount_init(void)
{
	if (!proc_create("mymounts", 0644, NULL, &proc_fops))
	{
		printk(KERN_ERR "Error init module /proc/%s\n", "mymount");
		return -EFAULT;
	} 
	else
		printk(KERN_INFO "Init module mounted /proc/%s created\n", "mymount");
	return 0;
}

void __exit mymount_exit(void)
{
	remove_proc_entry("mymounts", NULL);
	printk(KERN_INFO "Rm module mounted: /proc/%s removed\n", "mymount");
}

module_init(mymount_init);
module_exit(mymount_exit);

