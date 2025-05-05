/* Linux Kernel Module with file operations open, releasw, read and, write */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define N "d"
#define B 1024

static int m;
static char b[B];

static int o(struct inode *i, struct file *f) {
    printk(KERN_INFO "o\n");
    return 0;
}

static int c(struct inode *i, struct file *f) {
    printk(KERN_INFO "c\n");
    return 0;
}

static ssize_t r(struct file *f, char __user *u, size_t s, loff_t *o) {
    int l = strlen(b);
    if(s > l) s = l;
    if(copy_to_user(u, b, s))return -EFAULT;
    printk(KERN_INFO "r: %s\n", b);
    b[0]='\0';
    return s;
}

static ssize_t w(struct file *f, const char __user *u, size_t s, loff_t *o) {
    if (s > B - 1) s = B - 1;
    if (copy_from_user(b, u, s)) return -EFAULT;
    b[s] = '\0';
    printk(KERN_INFO "w: %s\n", b);
    return s;
}

static struct file_operations f = {
    .owner = THIS_MODULE,
    .open = o,
    .release = c,
    .read = r,
    .write = w,
};

static int __init x(void) {
    m = register_chrdev(0, N, &f);
    if (m < 0) return m;
    printk(KERN_INFO "x: %d\n", m);
    return 0;
}

static void __exit y(void) {
    unregister_chrdev(m, N);
    printk(KERN_INFO "y\n");
}

module_init(x);
module_exit(y);

MODULE_LICENSE("GPL");

