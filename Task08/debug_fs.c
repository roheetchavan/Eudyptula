/*
 * Debugfs device driver for Task 08 of eudyptula challenge
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

#include <linux/debugfs.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

static const char msg[] = "ebfdde43b12a";

static DEFINE_SEMAPHORE(foo_sem);

static struct dentry *debug_dir;
static struct dentry *debug_file_id;

static ssize_t id_read(struct file *f, char __user *buf,
			    size_t len, loff_t *off)
{
	return simple_read_from_buffer(buf, len, off, msg, sizeof(msg));
}

static ssize_t id_write(struct file *f, const char *buf,
			     size_t len, loff_t *off)
{
	ssize_t ret;
	/* allocate 1 more byte in case buffer is longer than msg lenght */
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

static const struct file_operations id_fops = {
	.owner = THIS_MODULE,
	.read = id_read,
	.write = id_write
};

static int __init debugfs_init(void)
{
	pr_err("init debugfs");

	/* Create subdir with name eudyptula */
	debug_dir = debugfs_create_dir("eudyptula", NULL);
	if (debug_dir == NULL) {
		pr_err("dir create failed");
		return -ENOMEM;
	}

	/* create file with name id and give all rw permissions */
	debug_file_id = debugfs_create_file("id", 0666,	debug_dir,
					    NULL, &id_fops);
	if (!debug_file_id) {
		pr_err("id create failed");
		debugfs_remove(debug_dir);
		return -ENOMEM;
	}

	return 0;
}

static void __exit debugfs_exit(void)
{
	pr_err("exit debugfs");
	debugfs_remove_recursive(debug_dir);
}

MODULE_AUTHOR("Rohit Chavan");
MODULE_DESCRIPTION("A simple debugfs device driver example");

module_init(debugfs_init);
module_exit(debugfs_exit);
