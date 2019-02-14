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

	tty.clear();
	tty.puts("booting...\n");

	// check magic
	tty.printf("magic=%x", magic);
	if(magic == MULTIBOOT2_BOOTLOADER_MAGIC)
		tty.puts("\t[ok]\n");

	tty.printf("addr=%x\n", addr);

	auto tag = (multiboot_tag*) (addr + 8);

	while(tag->type != MULTIBOOT_TAG_TYPE_END){
		tty.printf("tag type=%d, size=%x\n", tag->type, tag->size);

		switch(tag->type){
		case MULTIBOOT_TAG_TYPE_CMDLINE:
			tty.puts("\tcmdline: ");
			tty.puts(((multiboot_tag_string*)tag)->string);
			break;
		case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
			tty.puts("\tboot loader: ");
			tty.puts(((multiboot_tag_string*)tag)->string);
			break;
		case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
			tty.printf("\tlower=%x, upper=%x",
					((multiboot_tag_basic_meminfo*)tag)->mem_lower,
					((multiboot_tag_basic_meminfo*)tag)->mem_upper);
			break;
		}
		tty.puts("\n");

		tag = (multiboot_tag*) ((multiboot_uint8_t*) tag + ((tag->size+7) & ~7));
	}

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
