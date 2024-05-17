// Ideally, you should have a class that acts like the OS and runs the reset sequence, as well as a class that is in charge of handling the memory.

/* 
move CPU functions into other classes (OS,memory, CPU)
tenative list:
Memory:
1)loadword
2)loadbyteunsigned
3)store word
4)storebyte
5)read8/16/32
6)write8/16/32

OS:
1) jump
2) Jumpandlink
3) jumpregister

CPU: 
1)shiftleftlogical
2)shiftrightlogical
3)shiftleftarithmetic
4)shiftrightarithmetic
5) various ops like subtract,add, or

note: use dependancy injection instead of inheritance

lecture:
image: image that varies based on individual computer (GPU)

input: tests io (a/b, up/down, left/right, select/start, stdin)
*/