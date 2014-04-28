#ifndef SCULL_FILE_H 
#define SCULL_FILE_H

#include <linux/cdev.h>
#include <linux/fs.h>

#define SCULL_QUANTUM 4000
#define SCULL_QSET 1000

struct scull_qset
{
    void **data;
    struct scull_qset*next;
};

struct scull_dev
{
    struct scul_qset *data;
    int quantum;
    int qset;
    unsigned long size;
    struct semaphore sem;
    struct cdev cdev;
};

int scull_trim(struct scull_dev* dev);
loff_t scull_seek(struct file*, loff_t, int);
ssize_t scull_read(struct file*, char __user*, size_t, loff_t*);
ssize_t scull_write(struct file*, const char __user*, size_t, loff_t*);
int scull_open(struct inode*, struct file*);
int scull_release(struct inode*, struct file*);

#endif
