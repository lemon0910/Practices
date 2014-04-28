#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include "scull_file.h"

MODULE_LICENSE("Dual BSD/GPL");

static int scull_major = 0;
static int scull_minor = 0;
static unsigned int scull_nr_devs = 1;

extern struct file_operations scull_fops;
struct scull_dev dev_info =
{
    .data = 0,
    .quantum = SCULL_QUANTUM,
    .qset = SCULL_QSET,
    .size = 0,
};

static int getDevNum(void)
{
    dev_t dev;
    int r = 0;
    if(scull_major)
    {
        dev = MKDEV(scull_major, scull_minor);
        r = register_chrdev_region(dev, scull_nr_devs, "scull");
    }
    else
    {
        r = alloc_chrdev_region(&dev, scull_minor, scull_nr_devs, "scull");
        scull_major = MAJOR(dev);
    }

    if(r < 0)
    {
        printk(KERN_WARNING"scull:cannot get major %d\n", scull_major);
        return r;
    }

    printk(KERN_ALERT"scull major is %d\n", scull_major);
    return r;
}

static void scull_setup_cdev(struct scull_dev* dev, int index)
{
    int err;
    dev_t devno = MKDEV(scull_major, scull_minor + index);
    cdev_init(&dev->cdev, &scull_fops);
    dev->cdev.owner = THIS_MODULE;
    dev->cdev.ops = &scull_fops;
    err = cdev_add(&dev->cdev, devno, 1);

    if(err)
    {
        printk(KERN_NOTICE"Error %d adding scull %d\n", err, index);
    }
}

static void scull_close_cdev(struct scull_dev* dev)
{
    cdev_del(&dev->cdev);
}

static int scull_init(void)
{
    int r = getDevNum();
    if(r < 0)
        return r;

    scull_setup_cdev(&dev_info, 0);
    return 0;
}

static void scull_exit(void)
{
    scull_trim(&dev_info);
    scull_close_cdev(&dev_info);
    dev_t dev = MKDEV(scull_major, scull_minor);
    unregister_chrdev_region(dev, 1);
}

module_init(scull_init);
module_exit(scull_exit);
