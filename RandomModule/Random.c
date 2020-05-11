#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/random.h>


#define VERSION "0.1"
#define AUTHOR "Quy Thanh - Tam Phuc - Thanh Vy"
#define DESCRIPTION "A module to create a random number"
#define MOD_NAME "Random"
#define CLASS_NAME "CRandom"


MODULE_LICENSE("GPL");
MODULE_VERSION(VERSION);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);


struct _dev_info {
	dev_t dev_num;
	struct class* dev_class;
	struct device* dev_file;
	struct cdev* cdev;
} dev_info;


static int Open(struct inode* inode, struct file* filp) {
	printk("Entry point open is called\n");
	return 0;
}

static int Release(struct inode* inode, struct file* filp) {
	printk("Entry point release is called\n");
	return 0;
}

static ssize_t Read(struct file* filp, char __user* ubuff, size_t size, loff_t* off) {

	printk("Entry point read is called\n");

	int rand;
	get_random_bytes(&rand, sizeof(rand));
	printk("Random number is %d\n", rand);
	if (copy_to_user(ubuff,&rand,size)== 0)
		return 0;
	else {
		printk("Failed\n");
		return -EFAULT;
	}

}

static ssize_t Write(struct file* filp, const char __user* ubuff, size_t size, loff_t* off) {
	printk("Entry point write is called\n");
	return 0;
}

static struct file_operations fops = {
	.open = Open,
	.release = Release,
	.read = Read,
	.write = Write,
};


static int __init InitRandom(void) {
	/* cap phat device number */
	if (alloc_chrdev_region(&dev_info.dev_num, 0, 1, MOD_NAME) < 0) {
		printk("Fail to register device number dynamically\n");
		return -1;
	}
	printk("Register device number dynamically successfully\n");
	printk("Major number: %d\n", MAJOR(dev_info.dev_num));
	printk("Minor number: %d\n", MINOR(dev_info.dev_num));
	
	/* tao device class */
	dev_info.dev_class = class_create(THIS_MODULE, CLASS_NAME);
	if (dev_info.dev_class == NULL) {
		printk("Fail to create module class\n");
		return -2;
	}
	printk("Create module class successfully\n");
	
	/* tao device file */
	dev_info.dev_file = device_create(dev_info.dev_class, NULL, dev_info.dev_num, NULL, MOD_NAME);
	if (IS_ERR(dev_info.dev_file)) {
		printk("Fail to create device file\n");
		return -3;
	}
	printk("Device file create successfully\n");

	/* dang ky cac entry point voi kernel */
	dev_info.cdev = cdev_alloc();
	if (dev_info.cdev == NULL) {
		printk("Fail to allocate cdev structure\n");
		return -4;
	}
	printk("Allocate cdev structure successfully\n");
	
	cdev_init(dev_info.cdev, &fops);
	
	if (cdev_add(dev_info.cdev, dev_info.dev_num, 1) < 0) {
		printk("Fail to bind cdev structure\n");
		return -5;
	}
	printk("Bind cdev structure successfully\n");
	
    return 0;
}

static void __exit ExitRandom(void) {
	/* giai phong device number */
	unregister_chrdev_region(dev_info.dev_num, 1);
	printk("Unregister device number successfully\n");
	
	/* xoa bo device file */
	device_destroy(dev_info.dev_class, dev_info.dev_num);
	printk("Destroy device file successfully");
	
	/* huy dang ky entry point voi kernel */
	cdev_del(dev_info.cdev);
	printk("Destroy cdev structure successfully\n");
	
	/* xoa bo device class */
	class_destroy(dev_info.dev_class);
	printk("Destroy module class successfully\n");
}


module_init(InitRandom);
module_exit(ExitRandom);
