# 前言

最近觉得自己之前蛮多基础课学的并不咋滴，便想再补补。前段时间突然看到清华的操作系统实验，于是乎就打算试试，一边学一边做实验，然后通过博客来记录记录。

# 实验内容

lab1 中包含一个 bootloader 和一个 OS。这个 bootloader 可以切换到 X86 保护模式，能够读磁盘并加载 ELF 执行文件格式，并显示字符。而这 lab1 中的 OS 只是一个可以处理时钟中断和显示字符的幼儿园级别 OS。

# 练习

## 练习1：理解通过make生成执行文件的过程。

`1.操作系统镜像文件ucore.img是如何一步一步生成的？`

打开命令行，执行以下命令

```
cd /home/moocos/ucore_lab/labcodes_answer/lab1_result
make V=
```

结果如下

```cmake
# 构建 Kernel 文件
+ cc kern/init/init.c
gcc -Ikern/init/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/init/init.c -o obj/kern/init/init.o
+ cc kern/libs/readline.c
gcc -Ikern/libs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/libs/readline.c -o obj/kern/libs/readline.o
+ cc kern/libs/stdio.c
gcc -Ikern/libs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/libs/stdio.c -o obj/kern/libs/stdio.o
+ cc kern/debug/kdebug.c
gcc -Ikern/debug/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/kdebug.c -o obj/kern/debug/kdebug.o
+ cc kern/debug/kmonitor.c
gcc -Ikern/debug/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/kmonitor.c -o obj/kern/debug/kmonitor.o
+ cc kern/debug/panic.c
gcc -Ikern/debug/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/debug/panic.c -o obj/kern/debug/panic.o
+ cc kern/driver/clock.c
gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/clock.c -o obj/kern/driver/clock.o
+ cc kern/driver/console.c
gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/console.c -o obj/kern/driver/console.o
+ cc kern/driver/intr.c
gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/intr.c -o obj/kern/driver/intr.o
+ cc kern/driver/picirq.c
gcc -Ikern/driver/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/driver/picirq.c -o obj/kern/driver/picirq.o
+ cc kern/trap/trap.c
gcc -Ikern/trap/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/trap.c -o obj/kern/trap/trap.o
+ cc kern/trap/trapentry.S
gcc -Ikern/trap/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/trapentry.S -o obj/kern/trap/trapentry.o
+ cc kern/trap/vectors.S
gcc -Ikern/trap/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/trap/vectors.S -o obj/kern/trap/vectors.o
+ cc kern/mm/pmm.c
gcc -Ikern/mm/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Ikern/debug/ -Ikern/driver/ -Ikern/trap/ -Ikern/mm/ -c kern/mm/pmm.c -o obj/kern/mm/pmm.o
+ cc libs/printfmt.c
gcc -Ilibs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/  -c libs/printfmt.c -o obj/libs/printfmt.o
+ cc libs/string.c
gcc -Ilibs/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/  -c libs/string.c -o obj/libs/string.o
+ ld bin/kernel
ld -m    elf_i386 -nostdlib -T tools/kernel.ld -o bin/kernel  obj/kern/init/init.o obj/kern/libs/readline.o obj/kern/libs/stdio.o obj/kern/debug/kdebug.o obj/kern/debug/kmonitor.o obj/kern/debug/panic.o obj/kern/driver/clock.o obj/kern/driver/console.o obj/kern/driver/intr.o obj/kern/driver/picirq.o obj/kern/trap/trap.o obj/kern/trap/trapentry.o obj/kern/trap/vectors.o obj/kern/mm/pmm.o  obj/libs/printfmt.o obj/libs/string.o
# 构建 BootLoader
+ cc boot/bootasm.S
gcc -Iboot/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Os -nostdinc -c boot/bootasm.S -o obj/boot/bootasm.o
+ cc boot/bootmain.c
gcc -Iboot/ -fno-builtin -Wall -ggdb -m32 -gstabs -nostdinc  -fno-stack-protector -Ilibs/ -Os -nostdinc -c boot/bootmain.c -o obj/boot/bootmain.o
+ cc tools/sign.c
# 使用 gcc 将 sign.c 编译成可执行文件
gcc -Itools/ -g -Wall -O2 -c tools/sign.c -o obj/sign/tools/sign.o
gcc -g -Wall -O2 obj/sign/tools/sign.o -o bin/sign
# 使用 ld 命令链接 bootasm.o、bootmain.o 至 bootblock.out
+ ld bin/bootblock
ld -m    elf_i386 -nostdlib -N -e start -Ttext 0x7C00 obj/boot/bootasm.o obj/boot/bootmain.o -o obj/bootblock.o
'obj/bootblock.out' size: 488 bytes
build 512 bytes boot sector: 'bin/bootblock' success!
# 构建 ucore.img
# 使用 dd 工具创建 ucore.img 空文件夹
dd if=/dev/zero of=bin/ucore.img count=10000
10000+0 records in
10000+0 records out
5120000 bytes (5.1 MB) copied, 0.113584 s, 45.1 MB/s
dd if=bin/bootblock of=bin/ucore.img conv=notrunc
1+0 records in
1+0 records out
512 bytes (512 B) copied, 0.0018245 s, 281 kB/s
# 使用dd工具将文件bin/bootblock写入bin/ucore.img, 参数conv=notrunc表示不截断输出文件
dd if=bin/kernel of=bin/ucore.img seek=1 conv=notrunc
146+1 records in
146+1 records out
74923 bytes (75 kB) copied, 0.00668055 s, 11.2 MB/s
```

由以上输出大致为

+ 编译了若干内核文件，构建出内核 kernel
+ 生成 bootblock 引导程序
+ 生成 ucore.img 虚拟磁盘

![image-20200526192036913](upload\image-20200526192036913.png)

`2.一个被系统认为是符合规范的硬盘主引导扇区的特征是什么？`

在课程中有提示可通过 tools 目录下的 sign.c 文件了解，因此，查看 sign.c 文件

```c
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat st;
    if (argc != 3) {
        fprintf(stderr, "Usage: <input filename> <output filename>\n");
        return -1;
    }
    if (stat(argv[1], &st) != 0) {
        fprintf(stderr, "Error opening file '%s': %s\n", argv[1], strerror(errno));
        return -1;
    }
    printf("'%s' size: %lld bytes\n", argv[1], (long long)st.st_size);
    if (st.st_size > 510) {
        fprintf(stderr, "%lld >> 510!!\n", (long long)st.st_size);
        return -1;
    }
    char buf[512];
    memset(buf, 0, sizeof(buf));
    FILE *ifp = fopen(argv[1], "rb");
    int size = fread(buf, 1, st.st_size, ifp);
    if (size != st.st_size) {
        fprintf(stderr, "read '%s' error, size is %d.\n", argv[1], size);
        return -1;
    }
    fclose(ifp);
    buf[510] = 0x55;
    buf[511] = 0xAA;
    FILE *ofp = fopen(argv[2], "wb+");
    size = fwrite(buf, 1, 512, ofp);
    if (size != 512) {
        fprintf(stderr, "write '%s' error, size is %d.\n", argv[2], size);
        return -1;
    }
    fclose(ofp);
    printf("build 512 bytes boot sector: '%s' success!\n", argv[2]);
    return 0;
}

```

由以上代码大致可知

1. 大小为 512 字节，空余部分用 0 填充
2. 文件内容不超过 510 bytes
3. 最后两位为 0x55 0xAA

## 练习2：使用qemu执行并调试lab1中的软件

> 1. 从 CPU 加电后执行的第一条指令开始，单步跟踪 BIOS 的执行。
> 2. 在初始化位置 0x7c00 设置实地址断点,测试断点正常。
> 3. 从 0x7c00 开始跟踪代码运行,将单步跟踪反汇编得到的代码与 bootasm.S 和 bootblock.asm 进行比较。
> 4. 自己找一个 bootloader 或内核中的代码位置，设置断点并进行测试。

修改 tools/gdbinit 如下

```
set architecture i8086
target remote :1234
```

在 /home/moocos/ucore_lab/labcodes_answer/lab1_result 目录下执行命令 make debug

![image-20200526200018980](upload\image-20200526200018980.png)

分别输入 i r cs 、 i r eip 以及 x /2i 0xffff0 可以看到如下结果

![image-20200527124207631](upload\image-20200527124207631.png)

可知：

1.  CS 中地址为 0xF000, PC 中地址为 0xFFF0
2.  由课程内容可知，第一条指令执行位置在 0xffff0 处，并且为长跳转指令
3. BIOS 实例存储在 cs:ip 为 0xf000:0xe05b 处

接着，修改 gdbinit 如下

```
file obj/bootblock.o
set architecture i8086
target remote :1234
b *0x7c00
continue
```

继续 make debug

![image-20200527125030749](upload\image-20200527125030749.png)

可发现 0x7C00 为主引导程序的入口地址，代码与 bootasm.S 一致。

## 练习3：分析bootloader进入保护模式的过程。

> BIOS将通过读取硬盘主引导扇区到内存，并转跳到对应内存中的位置执行bootloader。请分析bootloader是如何完成从实模式进入保护模式的。
>
> 提示：需要阅读**小节“保护模式和分段机制”**和lab1/boot/bootasm.S源码，了解如何从实模式切换到保护模式，需要了解：
>
> - 为何开启A20，以及如何开启A20
> - 如何初始化GDT表
> - 如何使能和进入保护模式

`1.为何开启A20，以及如何开启A20`

先来说说 CPU 是如何寻址获取数据，i8086 处理器数据总线是 16 bit ，地址总线是 20 bit，寄存器 16 bit，因此，CPU 只能访问 1MB 以内的空间。CPU 想获取数据，需对 segment 左移 4 位，再加上 offest，最终形成一个 20bit 的地址

```
address = segment << 4 | offset
```

因此，理论上 20bit 地址可以访问 1MB 的内存空间。但在实模式下，这 20bit 的地址可以访问 (0x00000 ~ (0xffff0 + 0xffff = 0x10ffef)) 的存空间，大于 1MB。虽然大于 1MB，但对于 8086 来说，是没有任何影响，但是对于现在有更宽的地址总线的 CPU 来说，就会出现问题。在实模式下，这些 CPU 就能访问超过 1MB 的空间。为了解决这个问题，CPU 中添加了一个可控制 A20 地址线的模块，通过这个模块我们在实模式下将第 20 bit 的地址线限制为 0，这样 CPU 就无法访问超过 1MB 的空间了。

具体代码在 bootasm.S 文件中，然而没怎么看懂 orz

```asm
    # Enable A20:
    #  For backwards compatibility with the earliest PCs, physical
    #  address line 20 is tied low, so that addresses higher than
    #  1MB wrap around to zero by default. This code undoes this.
seta20.1:
    inb $0x64, %al                                  # Wait for not busy(8042 input buffer empty).
    testb $0x2, %al
    jnz seta20.1

    movb $0xd1, %al                                 # 0xd1 -> port 0x64
    outb %al, $0x64                                 # 0xd1 means: write data to 8042's P2 port

seta20.2:
    inb $0x64, %al                                  # Wait for not busy(8042 input buffer empty).
    testb $0x2, %al
    jnz seta20.2

    movb $0xdf, %al                                 # 0xdf -> port 0x60
    outb %al, $0x60                                 # 0xdf = 11011111, means set P2's A20 bit(the 1 bit) to 1
```

`2.如何初始化GDT表`

GDT(Global Descriptor Table, 全局描述表)。同实模式一样，在保护模式下，对内存的访问仍采用短地址加偏移地址的方式。其内存的管理方式有两种，段模式和页模式。在保护模式下，对于一个段的描述包括：Base Address，Limit（段的最大长度），Access（权限），这三个数据加在一起被放在一个 64 bit 的数据结构中，被称为段描述符。而由于寄存器为 16 bit，很明显，我们无法直接通过 16 bit 长度的寄存器来直接使用 64 bit 的段描述符。而对此的解决方案便是将这些段描述符放入一个全局数组中，将段寄存器中的值作为下标索引(段寄存器中的高 13 bit 的内容作为索引)来间接引用。而这个全局数组便是 GDT。

![image-20200527170905054](upload\image-20200527170905054.png)

![image-20200527170931967](upload\image-20200527170931967.png)

> GDT可以被放在内存的任何位置，那么当程序员通过段寄存器来引用一个段描述符时，CPU必须知道GDT的入口，也就是基地址放在哪里，所以 Intel的设计者门提供了一个寄存器GDTR用来存放GDT的入口地址，程序员将GDT设定在内存中某个位置之后，可以通过 LGDT 指令将 GDT 的入口地址装入此积存器，从此以后，CPU 就根据此积存器中的内容作为 GDT 的入口来访问GDT了。

代码中关于 GDT 表的定义以及初始化

```asm
asm.h 文件
/* Normal segment */
#define SEG_NULLASM                                             \
    .word 0, 0;                                                 \
    .byte 0, 0, 0, 0

#define SEG_ASM(type,base,lim)                                  \
    .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);          \
    .byte (((base) >> 16) & 0xff), (0x90 | (type)),             \
        (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

bootasm.S 文件

lgdt gdtdesc

gdt:
    SEG_NULLASM                                     # null seg
    SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)           # code seg for bootloader and kernel
    SEG_ASM(STA_W, 0x0, 0xffffffff)                 # data seg for bootloader and kernel

gdtdesc:
    .word 0x17                                      # sizeof(gdt) - 1
    .long gdt                                       # address gdt
```

`3.如何使能和进入保护模式`

开启 A20，初始化 GDT 后，将控制寄存器 CR0 的 PE 置为 1 即可

```
movl %cr0, %eax
orl 0x1, %eax
movl %eax, %cr0
```

由此，可总结出 bootloader 从实模式进入保护模式的过程

1. bootloader 开始运行在实模式，物理地址为 0x7C00
2. bootloader 关闭所有中断，方向标志位复位，ds，es，ss段寄存器清零 
3. 打开 A20 使之能够使用高位地址线 
4. 使用 lgdt 指令把 GDT 描述符表的大小和起始地址存入 GDT 寄存器，修改寄存器CR0的最低位（orl $CR0*_PE_*ON, %eax）完成从实模式到保护模式的转换，通过 ljmp 指令跳转到32位指令模式 
5. 进入保护模式后，设置ds，es，fs，gs，ss段寄存器，堆栈指针，便可以进入 c 程序 bootmain

## 练习4：分析bootloader加载ELF格式的OS的过程

> 通过阅读bootmain.c，了解bootloader如何加载ELF文件。通过分析源代码和通过qemu来运行并调试bootloader&OS，
>
> - bootloader如何读取硬盘扇区的？
> - bootloader是如何加载ELF格式的OS？

1. 定义指针 ELFHDR，指向 0x10000

2. 读取 8 个扇区大小的 ELF 头到 0x10000   `readseg((uintptr_t)ELFHDR, SECTSIZE * 8, 0);`

3. 检验文件是否符合格式 

       // is this a valid ELF?
       if (ELFHDR->e_magic != ELF_MAGIC) {
           goto bad;
       }

4. 循环调用readseg函数加载每一个程序段

5. 跳转到操作系统入口

## 练习5：实现函数调用堆栈跟踪函数

> 我们需要在lab1中完成kdebug.c中函数print_stackframe的实现，可以通过函数print_stackframe来跟踪函数调用堆栈中记录的返回地址。

```c
void
print_stackframe(void) {
     /* LAB1 YOUR CODE : STEP 1 */
     /* (1) call read_ebp() to get the value of ebp. the type is (uint32_t);
      * (2) call read_eip() to get the value of eip. the type is (uint32_t);
      * (3) from 0 .. STACKFRAME_DEPTH
      *    (3.1) printf value of ebp, eip
      *    (3.2) (uint32_t)calling arguments [0..4] = the contents in address (unit32_t)ebp +2 [0..4]
      *    (3.3) cprintf("\n");
      *    (3.4) call print_debuginfo(eip-1) to print the C calling function name and line number, etc.
      *    (3.5) popup a calling stackframe
      *           NOTICE: the calling funciton's return addr eip  = ss:[ebp+4]
      *                   the calling funciton's ebp = ss:[ebp]
      */
	uint32_t ebp = read_ebp(), eip = read_eip();
	int i, j;
	for(i = 0; ebp != 0 && i < STACKFRAME_DEPTH; i ++){
		cprintf("ebp: 0x%08x eip:0x%08x args:", ebp, eip);
		uint32_t *args = (uint32_t*)ebp + 2;
		for(j = 0; j < 4; j ++){
			cprintf("0x%08x  ", args[j]);
		}
		cprintf("\n");
		print_debuginfo(eip-1);
		eip = ((uint32_t*)eip)[1];
		ebp = ((uint32_t*)ebp)[0];
	}
}
```

在 lab1 目录下，命令行执行 make qemu

![image-20200527162304666](upload\image-20200527162304666.png)

## 练习6：完善中断初始化和处理

> 请完成编码工作和回答如下问题：
>
> 1. 中断描述符表（也可简称为保护模式下的中断向量表）中一个表项占多少字节？其中哪几位代表中断处理代码的入口？
> 2. 请编程完善kern/trap/trap.c中对中断向量表进行初始化的函数idt_init。在idt_init函数中，依次对所有中断入口进行初始化。使用mmu.h中的SETGATE宏，填充idt数组内容。每个中断的入口由tools/vectors.c生成，使用trap.c中声明的vectors数组即可。
> 3. 请编程完善trap.c中的中断处理函数trap，在对时钟中断进行处理的部分填写trap函数中处理时钟中断的部分，使操作系统每遇到100次时钟中断后，调用print_ticks子程序，向屏幕上打印一行文字”100 ticks”。

`1.中断描述符表（也可简称为保护模式下的中断向量表）中一个表项占多少字节？其中哪几位代表中断处理代码的入口？`

+ 一个表项占 8 个字节
+ ![image-20200527171123033](upload\image-20200527171123033.png)

`2.请编程完善kern/trap/trap.c中对中断向量表进行初始化的函数idt_init`

```c
void idt_init(void) {
	extern uintptr_t __vectors[];
	int i;
	for(i = 0; i < 256; i ++){
		SETGATE(idt[i], 0, GD_KTEXT, __vectors[i], DPL_KERNEL);
	}
	SETGATE(idt[T_SWITCH_TOK], 0, GD_KTEXT, __vectors[T_SWITCH_TOK], DPL_USER);
	lidt(&idt_pd);
}

```

`3.请编程完善trap.c中的中断处理函数trap`

```c
if (++ticks == TICK_NUM) {
  print_ticks();
  ticks = 0;
}
```

## 扩展练习 Challenge 1

> 扩展proj4,增加syscall功能，即增加一用户态函数（可执行一特定系统调用：获得时钟计数值），当内核初始完毕后，可从内核态返回到用户态的函数，而用户态的函数又通过系统调用得到内核态的服务。

在中断表中，可以看到 T_SWITCH_TOU 和 T_SWITCH_TOK，一个是切换到用户态，另一个是切换回内核态。切换时只需要修改段寄存器即可。

```C
static void
switch_to_user(struct trapframe *tf){
	if((tf->tf_cs & 3) == 3) return;
	tf->tf_ds = tf->tf_es = tf->tf_fs = tf->tf_gs = tf->tf_ss = USER_DS;
	tf->tf_cs = USER_CS;
	tf->tf_eflags |= FL_IOPL_3;
}

static void
switch_to_kernel(struct trapframe *tf) {
  if ((tf->tf_cs & 3) == 0) return;
  tf->tf_ds = tf->tf_es = tf->tf_fs = tf->tf_gs = tf->tf_ss = KERNEL_DS;
  tf->tf_cs = KERNEL_CS;
  tf->tf_eflags &= ~FL_IOPL_3;
}
...
...
case T_SWITCH_TOU:
    	switch_to_user(tf);
    	break;
case T_SWITCH_TOK:
        switch_to_kernel(tf);
        break;
```

这样的话，只要触发 T_SWITCH_TOU 和 T_SWITCH_TOK 编号的中断， CPU 指令流就会通过 ISR 执行到这里，并进行内核态和用户态的切换。

接下来只需要在 kern/init/init.c 中将 lab1_switch_test() 解注释，然后实现两个函数即可。

```c
static void
lab1_switch_to_user(void) {
    //LAB1 CHALLENGE 1 : TODO
	asm volatile (
			"sub $0x8, %%esp \n"
			"int %0 \n"
			"movl %%ebp, %%esp"
			:
			: "i"(T_SWITCH_TOU)
	    );
}

static void
lab1_switch_to_kernel(void) {
    //LAB1 CHALLENGE 1 :  TODO
	asm volatile (
		    "int %0 \n"
		    "movl %%ebp, %%esp \n"
		    :
		    : "i"(T_SWITCH_TOK)
		);
}
```

![](https://img2020.cnblogs.com/blog/1413964/202005/1413964-20200531150926062-1136332382.png)

## 扩展练习 Challenge 2

> 用键盘实现用户模式内核模式切换。具体目标是：“键盘输入3时切换到用户模式，键盘输入0时切换到内核模式”。 基本思路是借鉴软中断(syscall功能)的代码，并且把trap.c中软中断处理的设置语句拿过来。

击键会触发中断，对其的处理在 IRQ_KBD case 处，直接判断是不是 '0' 或 '3' 即可。

```c
c = cons_getc();
		switch (c) {
		 case '0':
			switch_to_kernel(tf);
			print_trapframe(tf);
			break;
		 case '3':
			switch_to_user(tf);
			print_trapframe(tf);
			break;
		}
		cprintf("kbd [%03d] %c\n", c, c);
		break;
```

# 小节

感觉 lab1 跟计组和汇编挂钩蛮多，做了快一周，之前这两门课就学的不认真，很多东西都忘的差不多了，做起实验来真的是要命，各种看不懂 orz。感觉自己这两年摸鱼摸得有点多。。。。

# 参考

1. https://www.cnblogs.com/lsgxeva/p/8948153.html
2. [https://bravey.github.io/2019-09-08-%E5%AE%9E%E6%A8%A1%E5%BC%8F%E5%AF%BB%E5%9D%80%E6%96%B9%E5%BC%8F.html#%E5%AE%9E%E6%A8%A1%E5%BC%8F%E5%AF%BB%E5%9D%80%E6%96%B9%E5%BC%8F](https://bravey.github.io/2019-09-08-实模式寻址方式.html#实模式寻址方式)
3. https://zhuanlan.zhihu.com/p/25867829

4. https://wiki.osdev.org/IDT
5. https://xr1s.me/2018/05/15/ucore-lab1-report/
6. https://www.cnblogs.com/ECJTUACM-873284962/p/11178427.html

