#include "multiboot2.h"

#define VRAM	0xB8000

void cls(){
	volatile unsigned char* vram = (unsigned char*) VRAM;
	for(int i=0;i<80*24*2;i++)
		*(vram + i) = 1;
}

void putchar(int x, int y, int c){
	unsigned char* vram = (unsigned char*) VRAM;
	auto addr = vram + (x + y * 80)*2;
	*addr = c & 0xff;
	*(addr+1) = 7;
}

extern "C" void kmain(unsigned long magic, unsigned long addr){
	putchar(0, 1, 'A');
	while(1);
	return;
}
