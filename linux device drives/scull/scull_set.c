#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "scull.h"

extern int scull_major;
extern int scull_minor;

struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.llseek = scull_seek,
	.read = scull_read,
	.write = scull_write,
	.open = scull_open,
	.release = scull_release,
};


struct scull_qset* scull_follow(struct scull_dev* dev , int item)
{	
	struct scull_qset* first = dev->data;

	if(!first)
	{
		first = kmalloc(sizeof(struct scull_qset) , GFP_KERNEL);
		if(!first)
			return NULL;

		dev->data = first;	
	}
	
	int i = 0;
	struct scull_qset* dptr = first;
	
	while(true)
	{
		if(!dptr)
		{
			dptr = kmalloc(sizeof(struct scull_qset) , GFP_KERNEL);
			if(!dptr)
				return NULL;
			
			dptr->data = NULL;
			dptr->next = NULL;
		}

		if(item == i)
			break;

		dptr = dptr->next;
		i++;
	}

	return dptr;
}

int scull_trim(struct scull_dev* dev)
{
	struct scull_qset* next, *dptr;
	int qset = dev->qset;
	int i ;
	for(dptr = dev->data ; dptr ; dptr = next)
	{
		if(dptr->data)
		{	
			for(i = 0; i< qset ; i++)
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	
	dev->size = 0;
	dev->quantum = SCULL_QUANTUM;
	dev->qset = SCULL_QSET;
	dev->data = NULL;
	return 0;
}

loff_t scull_seek(struct file* filp , loff_t index , int counts )
{
	struct scull_dev *dev = filp->private_data;
	loff_t newops;
	
	switch(counts)
	{
		case 0:
			newops = index;
			break;
		case 1:
			newops = filp->f_pos + index;
			break;
		case 2:
			newops = dev->size + index;
			break;
		default:
			return -EINVAL;
	} 
	
	if(newops < 0)
		return -EINVAL;
	
	printk(KERN_ALERT"in scull seek\n");
	filp->f_pos = newops;
	return newops;
}

ssize_t scull_read(struct file* filp , char __user* data , size_t count , loff_t* f_pos)
{
	struct scull_dev* dev = filp->private_data;
	struct scull_qset* dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int item , s_pos , q_pos , rset;
	int itemsize = quantum * qset;
	
	int retval = 0;
	
//	if(down_interruptible(&dev->sem))
//		return -ERESTARTSYS;
	
	printk(KERN_ALERT "dev size is %d, f_pos is %ld\n", dev->size, *f_pos);
	if(*f_pos >= dev->size)
		goto out;
	
	printk(KERN_ALERT"f_pos ok\n");
	if(*f_pos + count > dev->size)
		count = dev->size - *f_pos;
	
	item = (int)*f_pos / itemsize;
	rset = (int)*f_pos % itemsize;
	
	s_pos = rset / quantum;
	q_pos = rset % quantum;
	
	printk("item is %d , rset is %d , s_pos is %d , q_pos is %d ,dev->data address is %ld\n");
	dptr = scull_follow(dev , item);
	
	if(dptr == NULL )
	{
		printk(KERN_ALERT"dptr NULL\n");
		goto out;
	}
	
	 printk("In scull_read dptr address is %ld , dptr->data address is %ld\n",dptr , dptr->data);

	if(!dptr->data)
	{
		printk("dptr->data NULL\n");
		goto out;
	}
	
	if(!dptr->data[s_pos])
	{
		printk("dptr->data[%d] NULL\n",s_pos);
		goto out;	
	}
	
	if(count > quantum - q_pos)
		count = quantum - q_pos;

	if(copy_to_user(data , dptr->data[s_pos] + q_pos , count))
	{
		retval = -EFAULT;
		printk(KERN_ALERT"copy_to_user error\n");
		goto out;
	}
	
	printk(KERN_ALERT"read from scull\n");
	*f_pos += count;
	retval = count;

out:
//	up(&dev->sem);
	return retval;
	
}

ssize_t scull_write(struct file* filp , const char __user* data , size_t count , loff_t* f_pos)
{
	struct scull_dev* dev = filp->private_data;
	struct scull_qset* dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int item , s_pos , q_pos , rset;
	int itemsize = quantum * qset;
	
	printk(KERN_ALERT"scull in write\n");
	int retval = ENOMEM;
//	if(down_interruptible(&dev->sem))
//		return -ERESTARTSYS;
	
	item = (int)*f_pos / itemsize;
	rset = (int)*f_pos % itemsize;
	s_pos = rset / quantum;
	q_pos = rset % quantum;
	
	printk("item is %d , rset is %d , s_pos is %d , q_pos is %d ,dev->data address is %ld\n");
	dptr = scull_follow(dev , item);
	
	if(dptr == NULL)
		goto out;
	
	if(!dptr->data)
	{
		dptr->data = kmalloc(qset * sizeof(char*) , GFP_KERNEL);
		if(!dptr->data)
			goto out;
		
		memset(dptr->data , 0 , sizeof(char*) * qset);
	}
	
	printk("In scull_write dptr address is %ld , dptr->data address is %ld\n",dptr , dptr->data);

	if(!dptr->data[s_pos])
	{
		dptr->data[s_pos] = kmalloc(quantum , GFP_KERNEL);
		if(!dptr->data[s_pos])
			goto out;
		memset(dptr->data[s_pos] , 0 , quantum);
	}

	if(count > quantum - q_pos)
		count = quantum - q_pos;

	if(copy_from_user(dptr->data[s_pos] + q_pos , data , count))
	{
		retval = -EFAULT;
		goto out;
	}
	
	printk(KERN_ALERT"write in scull\n");
	*f_pos += count;
	retval = count;
	if(*f_pos > dev->size)
	{
		printk(KERN_ALERT "dev size is %d, f_pos is %ld\n", dev->size, *f_pos);
		dev->size = *f_pos;
		printk(KERN_ALERT "dev size is %d, f_pos is %ld\n", dev->size, *f_pos);
	}

out:
//	up(&dev->sem);
	return retval;
}

int scull_open(struct inode* inode , struct file* filp)
{
	struct scull_dev* dev;
	dev = container_of(inode->i_cdev , struct scull_dev , cdev);
	filp->private_data = dev;
	
	if((filp->f_flags & O_ACCMODE) == O_WRONLY)
	{
		scull_trim(dev);
	}
	return 0;
}

int scull_release(struct inode* inode , struct file* filp)
{
//	struct scull_dev* dev = filp->private_data;
//	scull_trim(dev);
	printk("in scull_release\n");
	return 0;
}
