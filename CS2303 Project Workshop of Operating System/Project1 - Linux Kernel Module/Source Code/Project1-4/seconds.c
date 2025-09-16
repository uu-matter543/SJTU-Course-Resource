#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>

unsigned long begin, seconds;

static int myproc_show(struct seq_file *m, void *v)
{
  seconds = (jiffies - begin) / HZ;
  seq_printf(m, "seconds = %lu\n", seconds);
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
  begin = jiffies;
  proc_create("seconds", 0666, NULL, &myproc_proc_ops);
  pr_info("Created /proc/%s\n", "seconds");
  return 0;
}

static void __exit myproc_exit(void)
{
  remove_proc_entry("seconds", NULL);
  pr_info("Removed /proc/%s\n", "seconds");
}

module_init(myproc_init);
module_exit(myproc_exit);

MODULE_LICENSE("GPL");
