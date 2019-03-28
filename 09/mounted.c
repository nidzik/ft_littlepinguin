#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/mount.h>
#include <linux/nsproxy.h>
#include <linux/fs_struct.h>
#include <linux/slab.h>
/*
struct mnt_namespace {
        atomic_t                count;
        struct ns_common        ns;
        struct mount *  root;
        struct list_head        list;
        struct user_namespace   *user_ns;
        struct ucounts          *ucounts;
        u64                     seq;    // Sequence number to prevent loops 
        wait_queue_head_t poll;
        u64 event;
        unsigned int            mounts; // # of mounts in the namespace
        unsigned int            pending_mounts;
} __randomize_layout;

struct mount {
        struct hlist_node mnt_hash;
        struct mount *mnt_parent;
        struct dentry *mnt_mountpoint;
        struct vfsmount mnt;
        union {
                struct rcu_head mnt_rcu;
                struct llist_node mnt_llist;
};
*/
#include "/home/baptiste/linux-next/include/linux/kbd_kern.h"

size_t len;

ssize_t my_read(struct file *file, char *buf, size_t count, loff_t *pos)
{
	struct dentry *curdentry;
	char str[256] = {0};
	char tmp[256]; 
	int error_count; 
	char *path;

	len = 42;
	if (!file || !buf || !pos)
		return -EFAULT;
	if (*pos >= len-1)
		return 0 ;

	strcat(str, "root");
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
	error_count = copy_to_user((void *)buf ,str ,strlen(str));
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
	if (!proc_create("mymount", 0644, NULL, &proc_fops)) {
		printk(KERN_ERR "error creating %s\n", "mymount");
		return -EFAULT;
	} else {
		printk(KERN_INFO "/proc/%s created\n", "mymount");
	}
	return 0;
}

void __exit mymount_exit(void)
{
	remove_proc_entry("mymount", NULL);
	printk(KERN_INFO "/proc/%s removed\n", "mymount");
}

module_init(mymount_init);
module_exit(mymount_exit);

