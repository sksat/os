#include "common.h"
#include "multiboot_info.h"
#include "vram.h"
#include "tty.h"
#include "util.h"

void* operator new(size_t, void *buf){
	return buf;
}

void operator delete(void*, void*) noexcept {

}

multiboot::Info	_minfo;
VRAM::TextMode	_vram_text;
Tty				_tty;

extern "C" void kmain(multiboot::uint32_t magic, multiboot::uint32_t addr){
	multiboot::Info	*minfo	= nullptr;
	VRAM::Base	*vram		= nullptr;
	Tty			*tty		= nullptr;

	// multiboot info
	minfo = new(&_minfo) multiboot::Info();
	minfo->init(magic, addr);
	minfo->parse_tags();

	// VRAM
	if(minfo->is_vram_text())
		vram	= new(&_vram_text) VRAM::TextMode();
	else
		while(1); //TODO graphic mode
	vram->init(minfo->vram_addr(), minfo->vram_width(), minfo->vram_height());

	// tty
	tty = new(&_tty) Tty();
	tty->init(vram);

	tty->clear();
	tty->puts("booting...\n");

	// check magic
	tty->printf("magic=%x", magic);
	if(minfo->check_magic())
		tty->puts("\t[ok]\n");
	tty->printf("addr=%x\n", addr);

	tty->printf("multiboot tag num=%d\n", minfo->get_tag_num());

	tty->puts("boot loader: ");
	tty->puts(minfo->bootloader());
	tty->puts("\n");

	auto meminfo = minfo->tags.basic_meminfo;
	tty->printf("Memory: lower=%x, upper=%x\n", (uint64_t)meminfo->lower, (uint64_t)meminfo->upper);

	auto vraminfo = minfo->tags.framebuffer;

	tty->printf("VRAM: addr=%x, pitch=%d, width=%d, height=%d, bpp=%d, mode=",
			vraminfo->common.addr,
			vraminfo->common.pitch,
			vraminfo->common.width,
			vraminfo->common.height,
			(int)vraminfo->common.bpp);

	switch(vraminfo->common.ftype){
		using namespace multiboot;
		case FrameBuffer::indexed:
			tty->puts("indexed\n");
			break;
		case FrameBuffer::rgb:
			tty->puts("RGB\n");
			break;
		case FrameBuffer::text:
			tty->puts("text\n");
			break;
	}

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
