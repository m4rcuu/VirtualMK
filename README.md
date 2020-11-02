# VirtualMK

VirtualMK is a simple virtual machine. You can pass it file for instance ```test.mk``` which contains numbers and the instructions:
```
  psh 1 psh 2
  add s
  mov s a
  prt
  hlt
```
Which is passed as an argument to the program ```.\VirtualMK.exe .\test.mk``` and it will execute the program. It should report any errors it encounters.

## Registers
```
S	0 :: stack
A	1 :: register A
B	2 :: register B
C	3 :: register C
D	4 :: register D
E	5 :: register E
F	6 :: register F
```

## Instructions
```
HLT	0  :: halts program
	
PSH	1  :: {value} pushes value to stack
	
POP	2  :: pops value from stack
	
ADD	3  :: {S} adds second value to first in stack
	      {A-F} {A-F} {A-F} adds second value of register to first and writes to third
	
SUB	4  :: {S} subtracts second value from first in stack
	      {A-F} {A-F} {A-F} subtracts second value of register from first and writes to third
	
MUL	5  :: {S} multiplies first value by second in stack
	      {A-F} {A-F} {A-F} multiplies first value of register by second and writes to third
	
DIV	6  :: {S} divides first value by second in stack
	      {A-F} {A-F} {A-F} divides first value of register by second and writes to third
	      
POW	7  :: {S} first value to power of second value in stack
	      {A-F} {A-F} {A-F} first value of register to power of second registry and writes to third
	
SQR	8  :: {S} square root of first value in stack
	      {A-F} square root of registry value 
	
LOG	9  :: {S} decimal logarithm of first value in stack
	      {A-F} decimal logarithm of registry value
	
LON	10 :: {S} natural logarithm of first value in stack
	      {A-F} natural logarithm of registry value 
	
EXP	11 :: {S} euler number to power of first value in stack
	      {A-F} euler number to power of registry value
	
MOV	12 :: {S, A-F} {S, A-F} moves values between registers and stack
	
SET	13 :: {S, A-F} {S, A-F} sets first value as second
	
PRT	14 :: prints stack and registers
	
NOP	15 :: does nothing
```

This was written with a ton of help from [this blog post](https://felixangell.com/blogs/virtual-machine-in-c) by Felix Angell.