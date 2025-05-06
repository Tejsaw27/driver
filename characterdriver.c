#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/uaccess.h>

#define DEVICE_NAME "chardev_example"
#define BUF_LEN 1024

static int major ;
static char msg[BUF_LEN];
static short msg_len;

