# CS2303 操作系统课程设计

2024-2025-2 学期，**吴晨涛**老师 **过敏意**老师 讲授

课程**CS2310 现代操作系统**的配套课程设计

内容为如下 8 个 Project（主要内容来自参考书《Operating System Concepts 10th Edition》第1~10章）

所用虚拟机参数：`VirtualBox 7.1.4` `Ubuntu 24.04 - Linux Kernel 6.11.0`

## Project 1

- 内核模块：在读取`/proc/jiffies`时报告`jiffies`的当前值
- 内核模块：在读取`/proc/seconds`时报告内核模块加载后经过的秒数

## Project 2

- 实现Shell接口`osh>`接受用户命令并执行
  - 创建子进程并在子进程中执行命令
  - 提供历史记录功能
  - 提供输入输出重定向功能
  - 允许父子进程通过管道进行通信
- 内核模块：将一个进程标识符写入`/proc/pid`，读取`/proc/pid`时将输出：
  - 该任务正在运行的命令
  - pid值

## Project 3

- 使用`C`的`Pthread API`创建11个子线程校验数独
  - 1个子线程校验数独中的所有行
  - 1个子线程校验数独中的所有列
  - 9个子线程分别校验9个3x3区域
- 使用`C`的`Pthread API`创建3个子线程
  - 2个子线程做一半数组的排序
  - 1个子线程将2个有序子数组合并为1个有序数组
- 使用`Java`的`Fork-Join API`并行实现排序算法
  - 归并排序
  - 快速排序

## Project 4

- 实现CPU调度算法
  - 先到先服务`FCFS`
  - 最短作业优先`SJF`
  - 优先级调度`Priority`
  - 轮询调度`RR`
  - 多级优先队列轮询调度`Priority-RR`
- 解决创建任务队列时获取`tid`的同步问题
- 报告调度算法的性能参数
  - 平均响应时间
  - 平均等待时间
  - 平均周转时间

## Project 5

- 使用`Pthread API`实现为任务分配线程执行的线程池
- 使用`Pthread API`信号量和互斥锁解决生产者消费者问题

## Project 6

- 编写程序实现银行家算法
  - 初始化全局变量，`available`从命令行读取，`allocation`初始为0， `maximum`，`need`从`input.txt`读取
  - 指令`*`打印`available`，`maximum`，`allocation`，`need`数组的值
  - 指令`RQ <pid> <resource[1..4]>`请求资源
  - 指令`RL <pid>`释放资源

## Project 7

- 实现连续内存分配器，最小粒度为4KB的页，支持用户的3种指令
  - 指令`STAT`打印当前状态
  - 指令`RQ <name> <size> <strategy>`为进程申请连续内存
  - 指令`RL <name>`释放进程的所有内存
- `<strategy>`对应3种内存分配策略
  - `F`对应首次适应First-fit
  - `B`对应最优适应Best-fit
  - `W`对应最差适应Worst-fit
- 为分配器实现有序双链表，使用双链表将空闲块按大小顺序链接，以加速最优适应和最差适应策略

## Project 8

- 实现虚拟内存管理器，将虚拟地址翻译成物理地址
  - 从`address.txt`文件读取逻辑地址
  - 使用TLB和页表进行地址翻译得到物理地址
  - 利用物理地址从物理内存中读取内容
  - 从`BACKING_STORE.bin`文件加载页面到物理内存以处理缺页错误，并更新页表和TLB
  - 统计并报告TLB命中率和物理内存命中率
