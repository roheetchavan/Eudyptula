#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rohit Chavan");
MODULE_DESCRIPTION("Simple module for Task01");

static int __init task_start(void)
{
	pr_debug("Hello World!\n");
	return 0;
}

static void __exit task_stop(void)
{
	pr_debug("Goodbye World!\n");
}

module_init(task_start);
module_exit(task_stop);
