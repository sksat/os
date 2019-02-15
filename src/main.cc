#include "multiboot2.h"
#include "common.h"
#include "vram.h"
#include "tty.h"
#include "util.h"
#include "multiboot_info.h"

#define VRAM_ADDR	(addr_t)0xB8000
#define COLUMNS		80
#define LINES		24
#define ATTRIBUTE	7

extern "C" void kmain(multiboot::uint32_t magic, multiboot::uint32_t addr){
	multiboot::Info minfo(magic, addr);
	minfo.parse_tags();

	VRAM::TextMode vram(VRAM_ADDR, COLUMNS, LINES);
	Tty tty(&vram);

	tty.clear();
	tty.puts("booting...\n");

	// check magic
	tty.printf("magic=%x", magic);
	if(minfo.check_magic())
		tty.puts("\t[ok]\n");
	tty.printf("addr=%x\n", addr);

	tty.printf("multiboot tag num=%d\n", minfo.get_tag_num());

	tty.puts("boot loader: ");
	tty.puts(minfo.bootloader());
	tty.puts("\n");

	auto meminfo = minfo.tags.basic_meminfo;
	tty.printf("Memory: lower=%x, upper=%x\n", meminfo->lower, meminfo->upper);

	auto vraminfo = minfo.tags.framebuffer;

	tty.printf("VRAM: addr=%x, pitch=%d, width=%d, height=%d, bpp=%d, mode=",
			vraminfo->common.addr,
			vraminfo->common.pitch,
			vraminfo->common.width,
			vraminfo->common.height,
			(int)vraminfo->common.bpp);

	switch(vraminfo->common.ftype){
		using namespace multiboot;
		case FrameBuffer::indexed:
			tty.puts("indexed\n");
			break;
		case FrameBuffer::rgb:
			tty.puts("RGB\n");
			break;
		case FrameBuffer::text:
			tty.puts("text\n");
			break;
	}

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
