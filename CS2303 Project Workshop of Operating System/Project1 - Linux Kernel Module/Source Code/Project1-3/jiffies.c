#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>

static int myproc_show(struct seq_file *m, void *v)
{
  seq_printf(m, "jiffies = %lu\n", jiffies);
  seq_printf(m, "HZ = %d\n", HZ);
  return 0;
}

static int myproc_open(struct inode *inode, struct file *file)
{
  return single_open(file, myproc_show, NULL);
}

static ssize_t myproc_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
{
  char kernel_buf[128];
  
  if (len >= sizeof(kernel_buf))
    return -EINVAL;

  if (copy_from_user(kernel_buf, buf, len))
    return -EFAULT;

  kernel_buf[len] = '\0';
  pr_info("Received from user space: %s\n", kernel_buf);
  return len;
}

static const struct proc_ops myproc_proc_ops = {
  .proc_open = myproc_open,
  .proc_read = seq_read,
  .proc_write = myproc_write,
  .proc_lseek = seq_lseek,
  .proc_release = single_release,
};

static int __init myproc_init(void)
{
  proc_create("jiffies", 0666, NULL, &myproc_proc_ops);
  pr_info("Created /proc/%s\n", "jiffies");
  return 0;
}

static void __exit myproc_exit(void)
{
  remove_proc_entry("jiffies", NULL);
  pr_info("Removed /proc/%s\n", "jiffies");
}

module_init(myproc_init);
module_exit(myproc_exit);

MODULE_LICENSE("GPL");
