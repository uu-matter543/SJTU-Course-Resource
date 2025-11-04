# 8086 Experiment 2

## 1 Memory Extension

### Experiment 1a

首先需要62256的使能信号CE为低电平激活，找到SRAM Address Decoder Circuit，发现两个62256共用74LS138的Y4，需要Addr19为0，Addr18-Addr16为100；同时上面62256要求Addr0为0，下面62256要求BHE为0即Addr0为1

综合分析可得上面62256的寻址范围为`0100 XXXX XXXX XXXX XXX0`，即`40000H~4FFFFH`中的偶地址；下面62256的寻址范围为`0100 XXXX XXXX XXXX XXX1`，即`40000H~4FFFFH`中的奇地址

### Experiment 1b

暂停 $\rightarrow$ Debug $\rightarrow$ Memory Contents U10/U11

### Experiment 1c

`80000H~8FFFFH`即`1000 XXXX XXXX XXXX XXXX`，最简单的方式就是将Addr19与Addr18两个引脚互换

## 2 8255 Operations

### Experiment 2a

8255片选CS为0，则使用74LS138中的Y2，所以Addr7-Addr3为10010；8255使用Data7-Data0作为数据通路，所以Addr0为0

所以8255的寻址为`XXXX XXXX XXXX 1001 0XX0`

PA对应`XXXX XXXX XXXX 1001 0000 == 90H`
PB对应`XXXX XXXX XXXX 1001 0010 == 92H`
PC对应`XXXX XXXX XXXX 1001 0100 == 94H`
CR对应`XXXX XXXX XXXX 1001 0110 == 96H`

### Experiment 2b

汇编代码解析见源代码

### Experiment 2c

汇编代码解析见源代码

### Experiment 2d

汇编代码解析见源代码

### Experiment 2e

此时8255的寻址为`XXXX XXXX XXXX 1001 0XX1`

PA对应`XXXX XXXX XXXX 1001 0001 == 91H`
PB对应`XXXX XXXX XXXX 1001 0011 == 93H`
PC对应`XXXX XXXX XXXX 1001 0101 == 95H`
CR对应`XXXX XXXX XXXX 1001 0111 == 97H`

其他步骤与实验2b~2d相同，略
