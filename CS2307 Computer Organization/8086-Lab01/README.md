# 8086 Expreiment 1

## Experiment 11

分析输入端口：要从U6A和U6B接收74LS244的信号，需选中U5处74LS138的Device1，又因为带圈引脚低电平有效，不带圈引脚高电平有效，所以使能信号Addr7-Addr6为10；数据通路选择信号Addr5-Addr3为000以选中74LS138的Y0，所以地址编码为`XXXX XXXX XXXX 1000 0XXX`，令`X`=`0`即得`80H`

同理可得输出端口地址编码为`XXXX XXXX XXXX 1000 1XXX`，令`X`=`0`即得`88H`

因此使用汇编指令`IN AL,80H`读取开关量状态，使用汇编指令`NOT AL`取反，使用`OUT AL,88H`送到输出端口显示，并循环执行即可

## Experiment 12

使用循环执行指令的方式实现模拟：`LOOP [label]`指令的含义为，若CX>0，则跳转到`label`处，并令CX-1，可用循环执行大量指令的方式实现不精确的延迟

`shortdelay`语句段执行`3FFFFH`条`LOOP`指令，`longdelay`语句段执行`0FFFFFH`条`LOOP`指令，分别对应短延迟和长延迟

```asm
shortdelay PROC
      PUSH CX
      MOV CX, 3FFFh
BACK: LOOP BACK
      POP CX
      RET
shortdelay ENDP

longdelay PROC
      PUSH CX
      MOV CX, 0FFFFh
BACK: LOOP BACK
      POP CX
      RET
longdelay ENDP
```

模拟红绿灯时，初态两向均为红灯，常态红绿灯阶段调用长延迟模拟，绿灯闪烁阶段循环调用短延迟模拟即可，如汇编代码所示

```asm
State0:   MOV AL,00110110B
          OUT PortOut,AL
          CALL shortdelay     ;初态：两向均为红灯
        
State1:   MOV AL,00110011B
          OUT PortOut,AL
          CALL longdelay      ;南北绿灯，东西红灯
        
          MOV CX,3
State2:   MOV AL,00110011B
          OUT PortOut,AL
          CALL shortdelay
          MOV AL,00110111B
          OUT PortOut,AL 
          CALL shortdelay                
          LOOP State2         ;南北绿灯闪烁，东西红灯
        
State3:   MOV AL,00110101B
          OUT PortOut,AL
          CALL shortdelay
          CALL shortdelay     ;南北黄灯，东西红灯
          MOV AL,00011110B
          OUT PortOut,AL
          CALL longdelay      ;南北红灯，东西绿灯
        
          MOV CX,3
State4:   MOV AL,00011110B
          OUT PortOut,AL
          CALL shortdelay
          MOV AL,00111110B
          OUT PortOut,AL 
          CALL shortdelay                 
          LOOP State4         ;南北红灯，东西绿灯闪烁
        
State5:   MOV AL,00101110B
          OUT PortOut,AL
          CALL shortdelay 
          CALL shortdelay     ;南北红灯，东西黄灯

          JMP State1
```

## Experiment 13

分析方法同Experiment11

`90H`=`XXXX XXXX XXXX 1001 0XXX`，关注Addr5-Addr3为010，对应U5处74LS138的Y2，因此将Device1端口改接到Y2处即可

`0A0H`=`XXXX XXXX XXXX 1010 0XXX`，关注Addr5-Addr3为100，对应U5处74LS138的Y4，因此将Device2端口改接到Y4处即可
