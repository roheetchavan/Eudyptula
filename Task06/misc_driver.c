/*
 * Misc device driver for Task 06 of eudyptula challenge
 */
#include <linux/module.h>

#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/major.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static const char msg[] = "ebfdde43b12a";

static ssize_t misc_read(struct file *f, char __user *buf,
			 size_t len, loff_t *off)
{
	return simple_read_from_buffer(buf, len, off, msg, sizeof(msg));
}

static ssize_t misc_write(struct file *f, const char *buf,
			  size_t len, loff_t *off)
{
	ssize_t ret;
	/* Allocate 1 more byte in case buffer is longer than msg lenght */
	char *msg_buffer = kcalloc(1, sizeof(msg) + 1, GFP_KERNEL);

	ret = simple_write_to_buffer(msg_buffer, sizeof(msg), off, buf, len - 1);
	if (ret < 0) {
		kfree(msg_buffer);
		return ret;
	}

	if (strncmp(msg, msg_buffer, sizeof(msg)) != 0) {
		kfree(msg_buffer);
		return -EINVAL;
	}

	kfree(msg_buffer);
	return len;
}


static const struct file_operations misc_fops = {
	.owner = THIS_MODULE,
	.read = misc_read,
	.write = misc_write
};

static struct miscdevice misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "eudyptula",
	.fops = &misc_fops
};

static int __init misc_init(void)
{
	int ret = 0;

	ret = misc_register(&misc_dev);
	if (ret)
		pr_alert("Unable to register misc device\n");

	return ret;
}

static void __exit misc_exit(void)
{
	misc_deregister(&misc_dev);
}

MODULE_AUTHOR("Rohit Chavan");
MODULE_DESCRIPTION("A simple misc char driver");

module_init(misc_init);
module_exit(misc_exit);
