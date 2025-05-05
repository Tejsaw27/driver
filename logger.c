#include<linux/module.h>
#include<linux/fs.h>

#define NAME "logger"

static dev_t dev;
static struct cdev my_cdev;

static int my_open(struct inode* inodep, struct file* filep){
  printk(KERN_INFO "device opened\n");
  return 0;
}

static int my_release(struct inode* inodep, struct file* filep){
  printk(KERN_INFO "device closed\n");
  return 0;
}

static ssize_t my_read(struct file* filep, char __user* user_buf, size_t size, loff_t* offsetp){
  printk(KERN_INFO "device read\n");
  return 0;
}

static ssize_t my_write(struct file* filep,const char __user* user_buf, size_t size, loff_t* offsetp){
  printk(KERN_INFO "written to the device\n");
  return 0;
}

struct file_operations f_ops = {
  .owner = THIS_MODULE,
  .open  = my_open,
  .release = my_release,
  .read = my_read,
  .write = my_write,
};

int __init my_init(void){
  int ret=alloc_chrdev_region(&dev,0,1,NAME); 
  if(ret<0)return ret;
  cdev_init(&my_cdev,&fops);
  ret = cdev_add(&my_cdev,dev,1);
  if (ret < 0) {
    printk(KERN_ERR "Failed to add cdev: %d\n", ret);
    unregister_chrdev_region(dev_number, 1); 
    return ret;
  }
  
  printk(KERN_INFO "module attached %u %u \n",MAJOR(dev),MINOR(dev));
  return 0;
}

void __exit my_exit(void){
  printk(KERN_INFO "module detached\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
