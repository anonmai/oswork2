#include "common.h"
#include "x86.h"
#include "device.h"

void kEntry(void) {
	/*
	asm volatile(        
		"movl $((80*3+11)*2), %edi\n\t" 
        "movb $33, %al\n\t"                   
        "movw %ax, %gs:(%edi)\n\t"              
		"1:      hlt\n\t"
		"jmp 1b"          );
		*/
	initSerial();// initialize serial port
	initIdt(); // initialize idt
	initIntr(); // iniialize 8259a
	initSeg(); // initialize gdt, tss
	loadUMain(); // load user program, enter user space

	while(1);
	assert(0);
}
