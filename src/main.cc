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

	tty.printf("addr=%x", addr);

	auto tag = (multiboot::tag*) (addr + 8);

	while(tag->type != multiboot::tag::End){
		using namespace multiboot;
		tty.printf("tag type=%d, size=%x\n", tag->type, tag->size);

		switch(tag->type){
		case tag::CmdLine:
			tty.puts("\tcmdline: ");
			tty.puts(((tag_string*)tag)->string);
			tty.puts("\n");
			break;
		case multiboot::tag::BootLoaderName:
			tty.puts("\tboot loader: ");
			tty.puts(((tag_string*)tag)->string);
			tty.puts("\n");
			break;
		case multiboot::tag::BasicMemInfo:
			tty.printf("\tlower=%x, upper=%x\n",
					((tag_basic_meminfo*)tag)->mem_lower,
					((tag_basic_meminfo*)tag)->mem_upper);
			break;
		case multiboot::tag::FrameBuffer:
			{
				auto t = (tag_framebuffer*)tag;
				tty.printf("\taddr=%x, pitch=%d\n",
						t->common.addr,
						t->common.pitch);
				tty.printf("\twidth=%d, height=%d, bpp=%d",
						t->common.width,
						t->common.height,
						t->common.bpp);
			}
		default:
			break;
		}

		tag = (multiboot::tag*) ((multiboot::uint8_t*) tag + ((tag->size+7) & ~7));
	}

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
