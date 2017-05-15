/**
 * task05:when any USB keyboard is plugged in,the module will be automatically
 *	  loaded by the correct userspace hotplug tools (which are implemented
 *	  by depmod / kmod / udev / mdev / systemd, depending on what distro.)
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

/* Ref:drivers/hid/usbhid/usbkbd.c */
#include <linux/usb.h>
#include <linux/hid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rohit Chavan");
MODULE_DESCRIPTION("Test version of USB HID Boot Protocol keyboard driver");

/**
 *usb_device_id:Structure that describes the types of USB devices
 *		this driver supports
 */
static struct usb_device_id usb_kbd_id_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
			     USB_INTERFACE_SUBCLASS_BOOT,
			     USB_INTERFACE_PROTOCOL_KEYBOARD) },
	{}	/* Terminating entry */
};

MODULE_DEVICE_TABLE (usb, usb_kbd_id_table);

static int __init usbkbd_init(void)
{
	pr_info("[*]usbkbd initialized successfully.\n");

	return 0;
}

static void __exit usbkbd_exit(void)
{
	pr_info("[*]usbkbd removed from system.\n");
	return;
}

module_init(usbkbd_init);
module_exit(usbkbd_exit);
