# CS2306 计算机系统结构实验

2024-2025-2，**苏锐丹**老师 讲授

课程**CS2305 计算机系统结构**的配套实验，目的是熟悉Vivado开发流程，并用Vivado Verilog逐步实现完整支持MIPS32指令集的五级指令流水CPU

IDE参数：`Vivado 2018.3`

内容：

## Lab01

- 熟悉Xilinx逻辑设计工具Vivado开发流程
- 了解Verilog描述硬件功能行为的逻辑
- 通过仿真检验电路设计是否预期
- 学习为烧录至开发板添加管脚约束
- 利用开发板的LED实现流水灯的功能
- 体会系统硬件开发的基本实验流程

## Lab02

- 掌握Xilinx逻辑设计工具Vivado的基本操作
- 利用Verilog进行简单的逻辑设计
- 通过仿真检验设计是否符合预期
- 约束文件的使用和直接写法
- 生成Bitstream文件并烧录至开发板验证

## Lab03

- 熟悉MIPS32指令集
- 理解控制单元、ALU控制单元、ALU单元的原理
- 使用Verilog设计与实现控制单元
- 使用Verilog设计与实现ALU控制单元
- 使用Verilog设计与实现ALU单元
- 使用Vivado进行功能模块的行为仿真

## Lab04

- 理解寄存器、数据内存、符号扩展单元的原理
- 使用Verilog设计与实现寄存器
- 使用Verilog设计与实现数据内存
- 使用Verilog设计与实现符号扩展单元
- 使用Vivado进行功能模块的行为仿真

## Lab05

- 简单的类MIPS单周期处理器的工作原理
  - 指令执行时的数据通路
  - 数据通路的控制线路
  - 各功能部件间的互联定义
  - 逻辑选择关系
- 简单的类MIPS单周期处理器的设计与实现
  - 9条基本指令(lw, sw, beq, add, sub, and, or, slt, j)CPU的实现与调试
  - 扩展至16条指令(增加addi, andi, ori, sll, srl, jal, jr)CPU的设计与实现
- 仿真测试与上板验证（以乘法器的汇编代码为例）

## Lab06

- 理解CPU Pipeline的基本原理、流水线冒险(hazard)及数据依赖关系，在MIPS 32单周期CPU的基础上，设计简单流水线CPU
- 设计Forwarding机制，通过检测竞争，在数据冒险发生时进行数据前递，以解决Read-after-Write数据冒险，并减少因Read-after-Write数据冒险带来的流水线停顿延时，提高流水线处理器性能
- 增加Stall机制，解决Load-Use数据冒险，以避免Forwarding机制无法解决Load-Use数据冒险而导致的错误
- 通过Predict-not-taken策略解决控制冒险，最大化减少控制竞争带来的流水线停顿延时，进一步提高处理器性能
- 将CPU支持的指令数量从16条扩充为31条，使处理器功能更加丰富，基本实现支持MIPS32指令集的指令流水处理器
