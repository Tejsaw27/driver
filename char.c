/*Write a basic character device driver that registers a /dev/mychardev device.
Implement read() and write() operations for a character driver and test using cat and echo.
Modify a character driver to use circular buffer for storing data.*/

#include <linux/fs.h>
#include <linux/cdev.h>

#define DEVICE_NAME "chardev"

static dev_t dev_num;        
static struct cdev my_cdev; 

static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *pos);
static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *pos);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "chardev: device opened\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "chardev: device closed\n");
    return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t count, loff_t *pos) {
    size_t bytes_to_read;

    if (data_size == 0) {
        printk(KERN_INFO "mychardev: Buffer is empty\n");
        return 0; // No data to read
    }

    bytes_to_read = min(count, (size_t)data_size);

    if (copy_to_user(buf, &circular_buffer[read_pos], bytes_to_read)) {
        return -EFAULT;
    }

    read_pos = (read_pos + bytes_to_read) % BUFFER_SIZE;
    data_size -= bytes_to_read;

    printk(KERN_INFO "mychardev: Read %zu bytes\n", bytes_to_read);
    return bytes_to_read;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t count, loff_t *pos) {
    size_t bytes_to_write;





    printk(KERN_INFO "chardev: frote %zu bytes\n", bytes_to_write);
    return bytes_to_write;
}

static int __init mychardev_init(void) {
    int ret;

    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "chardev: failed to allocate device number\n");
        return ret;
    }

    cdev_init(&my_cdev, &fops);
    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "chardev: failed to add cdev\n");
        return ret;
    }


    printk(KERN_INFO "chardev: loaded\n");
    return 0;
}

static void __exit mychardev_exit(void) {
    kfree(circular_buffer);         
    cdev_del(&my_cdev);              
    unregister_chrdev_region(dev_num, 1);

    printk(KERN_INFO "chardev: unloaded\n");
}

module_init(mychardev_init);
module_exit(mychardev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("shivam");
MODULE_DESCRIPTION("char dev driver");

