#include "multiboot2.h"
#include "common.h"
#include "vram.h"
#include "tty.h"

#define VRAM_ADDR	(addr_t)0xB8000
#define COLUMNS		80
#define LINES		24
#define ATTRIBUTE	7

extern "C" void kmain(unsigned long magic, unsigned long addr){
	VRAM::TextMode vram(VRAM_ADDR, COLUMNS, LINES);
	Tty tty(&vram);

	tty.puts("hello, world!\n");
	tty.puts("tab\ttest\n");

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
