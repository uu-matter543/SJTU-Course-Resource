#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

static struct proc_dir_entry *my_proc_file;
static long l_pid;

static int my_proc_show(struct seq_file *m, void *v)
{
  seq_printf(m, "Hello from /proc/my_proc\n");
  struct task_struct *tsk = NULL;
  tsk = pid_task(find_vpid(l_pid), PIDTYPE_PID);
  if (tsk == NULL)
  {
    seq_printf(m, "No such pid\n");
    return 0;
  }
  seq_printf(m, "pid: [%d], name: [%s], state: [%u], prio: [%d], vruntime: [%llu]\n",
                tsk->pid, tsk->comm, tsk->__state, tsk->prio, tsk->se.vruntime);
  return 0;
}

static int my_proc_open(struct inode *inode, struct file *file)
{
  return single_open(file, my_proc_show, NULL);
}

static ssize_t my_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
  char data[128];
  if (count > sizeof(data) - 1) return -EINVAL;
  if (copy_from_user(data, buffer, count)) return -EFAULT;
  data[count] = '\0';
  printk(KERN_INFO "/proc/my_proc received: %s", data);
  sscanf(data, "%ld", &l_pid);
  return count;
}

static const struct proc_ops my_proc_fops = {
  .proc_open = my_proc_open,
  .proc_read = seq_read,
  .proc_write = my_proc_write,
  .proc_lseek = seq_lseek,
  .proc_release = single_release,
};

static int __init my_proc_init(void)
{
  my_proc_file = proc_create("my_proc", 0666, NULL, &my_proc_fops);
  if (!my_proc_file)
  {
    pr_err("Failed to create /proc/my_proc\n");
    return -ENOMEM;
  }
  printk(KERN_INFO "Created /proc/my_proc\n");
  return 0;
}

static void __exit my_proc_exit(void)
{
  proc_remove(my_proc_file);
  printk(KERN_INFO "Removed /proc/my_proc\n");
}

module_init(my_proc_init);
module_exit(my_proc_exit);

MODULE_LICENSE("GPL");
