#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/tty.h>
#include<linux/serial.h>
#include<linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

#define MAJOR_NUM 227
#define MINOR_NUM 0
#define DEV_NAME "dummy_driver"
#define MAJOR_ACM 240
#define MINOR_ACM 0

//static ssize_t write_to_device(struct file *file, const char __user *message, size_t count, loff_t *offset);
static int open_device(struct inode *inode, struct file *file);
static int close_device(struct inode *inode);

static struct file_operations fops = {
//  .write = write_to_device,
  .open = open_device,
  .release = close_device
};


static struct tty_struct *tty_acm = NULL;

static struct tty_struct *get_tty_acm(void)
{
  struct tty_struct *tty;
  struct tty_driver *tty_d;

  tty_d = tty_driver_lookup_tty(MAJOR_ACM, MINOR_ACM);
  if(!tty_d) {
    printk(KERN_ALERT "Error: Cannot find tty driver for ttyACM0!");
    return NULL;
  }

  tty= tty_open(tty_d, MKDEV(MAJOR_ACM, MINOR_ACM));
  if (IS_ERR(tty)) { 
    printk(KERN_ALERT "Error couldn't open ttyACM0!");
    return NULL;
  }

  return tty;
}

static int open_device(struct inode *inode, struct file *file)
{
  if (!tty_acm) {
    tty_acm = get_tty_acm();
    if (!tty_acm) {
      printk(KERN_ALERT "Couldn't get ttyACM0\n");
      return -ENODEV;
    }
  }
  return 0;
}

static int close_device(struct inode *inode)
{
  if (tty_acm) {
    tty_release(tty_acm);
    tty_acm = NULL;
  }
  printk(KERN_ALERT "Device %s is closed!\n", DEV_NAME);
  return 0;
}

// registring operations
int register_device(void)
{
  int result = register_chrdev(MAJOR_NUM, DEV_NAME, &fops); // check this one in ldd3
  if (result < 0) {
    printk(KERN_ALERT "%s: can't register device! Exiting with error number: %i!\n", DEV_NAME, result);
  }

  return result;
}

void unregister_device(void)
{
  printk(KERN_ALERT "Removing module!");
  unregister_chrdev(MAJOR_NUM, DEV_NAME);
  printk(KERN_NOTICE "%s has been succesfully unregistred!\n", DEV_NAME);
}

int driver_init(void)
{
  if (register_device() < 0) {
    return -1;
  }
  printk(KERN_ALERT "Device %s is succesfully registred with major number %d!\n", DEV_NAME, MAJOR_NUM);
  return 0;
}

void driver_exit(void)
{
  unregister_device();
  printk(KERN_ALERT "Goodbye, cruel world\n!");
}

module_init(driver_init);
module_exit(driver_exit);
