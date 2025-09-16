#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int simple_init(void)
{
  printk(KERN_INFO "Loading Kernel Module\n");
  return 0;
}

void simple_exit(void)
{
  printk(KERN_INFO "Removing Kernel Module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
