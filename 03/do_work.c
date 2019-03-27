// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/netdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nidzik <nidzik@student.42.fr>");
MODULE_DESCRIPTION("Do Work module");

static int do_work(int *my_int, int retval)
{
	int x, y, z;

	y = *my_int;
	pr_err("Run module !\n");
	for (x = 0; x < *my_int; ++x)
		udelay(10);
	if (y < 10)
		pr_info("We slept a long time!");
	pr_info("Yay\n");
	z = x * y;
	return z;
}

static int __init my_init(void)
{
	int x;

	pr_err("Init module...\n");
	x = 10;
	x = do_work(&x, x);
	return x;
}

static void __exit my_exit(void)
{
	pr_err("Exit module.\n");
}

module_init(my_init);
module_exit(my_exit);