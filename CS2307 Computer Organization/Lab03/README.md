# 8086 Experiment 3

## 1 8255 Operations

### EXperiment 1a

8255片选CS为0，则使用74LS138中的Y2，所以Addr8-Addr4为10010；8255使用Data15-Data8作为数据通路，所以Addr0为1

所以8255的寻址为`XXXX XXXX XXX1 0010 XXX1`

PA对应`XXXX XXXX XXX1 0010 X001 == 121H`
PB对应`XXXX XXXX XXX1 0010 X011 == 123H`
PC对应`XXXX XXXX XXX1 0010 X101 == 125H`
CR对应`XXXX XXXX XXX1 0010 X111 == 127H`

### Experiment 1b

分别选中4个数码管，然后依次写入学号后4位即可

### Experiment 1c

使用`AND AL,10111111B`的方式，`A&1=A`可保留某位的数据，`A&0=0`可清零某位的数据，保留除PC6之外的其他7位，而将PC6置零，其他类似的指令同理，具体可参见代码

## 2 8253 Operations

### EXperiment 2a

8253片选CS为0，则使用74LS138中的Y0，所以Addr8-Addr4为10000；8255使用Data7-Data0作为数据通路，所以Addr0为0

所以8255的寻址为`XXXX XXXX XXX1 0000 XXX0`

PA对应`XXXX XXXX XXX1 0000 X000 == 100H`
PB对应`XXXX XXXX XXX1 0000 X010 == 102H`
PC对应`XXXX XXXX XXX1 0000 X100 == 104H`
CR对应`XXXX XXXX XXX1 0000 X110 == 106H`

### EXperiment 2b

在Experiment 1c的基础上继续实验即可，关闭开关时不显示方波，打开开关时显示方波

### Experiment 2c

该实验即为时钟分频的原理，CLK0的频率降低到1%后即为CLK1的频率

## 3 Interrupt application 1

### Experiment 3cd

设置中断，`INT_INIT`代码段即中断初始化，设置中断向量表中`0ADH`处指向目标中断程序

软件调用中断，在代码中出现`INT IRQNum`表示调用中断向量表中`0ADH`处的中断

同时在`MYIRQ`代码段中设置改变D13的代码（类似Experiment 1c中读取PC0送入PC6的方式）

### Experiment 3e

硬件调用中断，在按钮按下后8086会在Data7-Data0处寻找中断向量号，根据中断向量号`0ADH`，设置DSW1的8-1开关状态分别为`10101101`，所以按下按钮后8086会执行中断向量表中`0ADH`处的中断处理程序，即反转D13的亮灭情况

## 4 Interrupt application 2

将CL作为数码管下标的寄存地址，在`MYIRQ`代码段中设置CL在4~1循环（每次中断时，CL自减，CL为0时重设为4）

循环过程中`DISPLAY8255`代码段每次只根据CL点亮特定的某1位，即可实现按下按钮改变显示的效果

## 5 Interrupt application 3

系统时钟周期为1微秒，设置OUT0的周期为10毫秒，OUT1的周期为1秒

每次OUTX（X=0,1）发出脉冲时，8086会调用中断程序，而中断程序为重置8253的T2计数器，模拟喂电子狗的行为

因此U15处CLK引脚接在OUT0时，可以及时喂电子狗，电子狗不会响起；U15处CLK引脚接在OUT1时，不能及时喂电子狗，电子狗会响起

## 6 Interrupt application 4

选择一个寄存器保存中断次数，每次产生中断时该寄存器自增，并在每次`DISPLAY8255`时展示该次数即可。不再给出项目文件
