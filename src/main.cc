#include "multiboot2.h"

#define VRAM		0xB8000
#define COLUMNS		80
#define LINES		24
#define ATTRIBUTE	7

// functions
void cls();
void putchar(int x, int y, int c);

extern "C" void kmain(unsigned long magic, unsigned long addr){
	cls();

	putchar(0, 1, 'A');
	putchar(1, 1, 'B');
	putchar(2, 1, 'C');

	while(1);
	return;
}

void cls(){
	volatile unsigned char* vram = (unsigned char*) VRAM;
	for(int i=0;i<COLUMNS*LINES*2;i++)
		*(vram+i) = 0;
}

void putchar(int x, int y, int c){
	volatile unsigned char *vram = (unsigned char*) VRAM;
	auto addr = vram + (x + y * COLUMNS)*2;
	*addr = c & 0xff;
	*(addr+1) = ATTRIBUTE;
}
