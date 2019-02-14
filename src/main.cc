#include "multiboot2.h"
#include "common.h"
#include "vram.h"
#include "tty.h"
#include "util.h"

#define VRAM_ADDR	(addr_t)0xB8000
#define COLUMNS		80
#define LINES		24
#define ATTRIBUTE	7

extern "C" void kmain(unsigned long magic, unsigned long addr){
	VRAM::TextMode vram(VRAM_ADDR, COLUMNS, LINES);
	Tty tty(&vram);

	char buf[COLUMNS];

	tty.clear();
	tty.puts("booting...\n");

	// check magic
	tty.printf("magic=%x", magic);
	if(magic == MULTIBOOT2_BOOTLOADER_MAGIC)
		tty.puts("\t[ok]\n");

	tty.printf("addr=%x\n", addr);

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
