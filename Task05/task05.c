/*
 * Purpose:when any USB keyboard is plugged in, the module will be
 *	   automatically loaded by the correct userspace hotplug tools.
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/usb.h>

/* disconnect_function:called on device removal */
static void kbd_disconnect(struct usb_interface *interface)
{
	pr_info("[*] KBD unplugged\n");
}

/* probe_function:called on device insertion if no other driver present */
static int kbd_probe(struct usb_interface *interface,
		     const struct usb_device_id *id)
{
	pr_info("[*] KBD (%04X:%04X) plugged\n",
	       id->idVendor, id->idProduct);
	return 0;
}

/* usb_device_id */
static struct usb_device_id kbd_table[] = {
	/* Put VendorID and ProductID of device obtained from lsusb
	 * 0bda:0138 Realtek USB2.0 CRW
	 */
	{ USB_DEVICE(0x0bda, 0x0138) },
	{} /* Terminating entry */
};
MODULE_DEVICE_TABLE(usb, kbd_table);

/* usb_driver */
static struct usb_driver kbd_driver = {
	.name = "My KBD driver",
	.id_table = kbd_table,	/* usb_device_id */
	.probe = kbd_probe,
	.disconnect = kbd_disconnect,
};

static int __init pen_init(void)
{
	int result;

	pr_info("[*] KBD driver\n");
	/* register this driver with the USB system */
	result = usb_register(&kbd_driver);
	if (result)
		pr_info("KBD driver registration error\n");

	return result;
}

static void __exit pen_exit(void)
{
	/* deregister this driver with usb subsystem */
	usb_deregister(&kbd_driver);
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rohit Chavan");
MODULE_DESCRIPTION("USB KBD registration module");

