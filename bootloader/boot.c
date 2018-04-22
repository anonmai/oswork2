#include "boot.h"

#define SECTSIZE 512

void bootMain(void) {
	/* 加载内核至内存，并跳转执行 */
	unsigned int sceno = 1;			//设置要读写的磁盘扇区号为1，即第二个磁盘扇区
	unsigned long va = 0x100000;		//设置要写入的内存地址为0x8c00
	for(int i=0;i<200;i+=1)
	{
		readSect((void*)va, sceno);
		sceno+=1;
	}
	
	asm volatile("jmp 0x100000");		//跳转到刚刚写入代码的位置执行
	while(1);						//无限循环
}

void waitDisk(void) { // waiting for disk
	while((inByte(0x1F7) & 0xC0) != 0x40);
}

void readSect(void *dst, int offset) { // reading a sector of disk
	int i;
	waitDisk();
	outByte(0x1F2, 1);
	outByte(0x1F3, offset);
	outByte(0x1F4, offset >> 8);
	outByte(0x1F5, offset >> 16);
	outByte(0x1F6, (offset >> 24) | 0xE0);
	outByte(0x1F7, 0x20);

	waitDisk();
	for (i = 0; i < SECTSIZE / 4; i ++) {
		((int *)dst)[i] = inLong(0x1F0);
	}
}
