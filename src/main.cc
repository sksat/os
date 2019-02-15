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

extern "C" void kmain(multiboot::uint32_t magic, multiboot::uint32_t addr){
	multiboot::Info	*minfo	= nullptr;
	VRAM::Base	*vram		= nullptr;

	// multiboot info
	minfo = new(&_minfo) multiboot::Info();
	minfo->init(magic, addr);
	minfo->parse_tags();

	// VRAM
	using VRAM::Color;
	if(minfo->is_vram_text())
		vram	= new(&_vram_text) VRAM::TextMode();
	else
		while(1); //TODO graphic mode
	vram->init(minfo->vram_addr(), minfo->vram_width(), minfo->vram_height());

	// tty
	Tty tty(vram);

	tty.clear();
	tty << "booting...\n";

	// check magic
	tty << "magic=" << Color::Red <<(uint64_t)magic << Color::White;
	if(minfo->check_magic())
		tty << "\t[ok]\n";
	tty << "addr=" << Color::Red << (uint64_t)addr << Color::White << "\n";

	tty << "multiboot tag num=" << minfo->get_tag_num() << "\n";

	tty << "boot loader: " << Color::Green << minfo->bootloader() << Color::White << "\n";

	auto meminfo = minfo->tags.basic_meminfo;
	tty << "Memory: lower=" << (uint64_t)meminfo->lower
		<< ", upper=" << (uint64_t)meminfo->upper << "\n";

	auto vraminfo = minfo->tags.framebuffer;

	tty << "VRAM: addr=" << (uint64_t)vraminfo->common.addr
		<< ", pitch=" << vraminfo->common.pitch
		<< ", width=" << vraminfo->common.width
		<< ", height="<< vraminfo->common.height
		<< ", bpp=" << (int)vraminfo->common.bpp
		<< ", mode=";

	switch(vraminfo->common.ftype){
		using namespace multiboot;
		case FrameBuffer::indexed:
			tty << "indexed\n";
			break;
		case FrameBuffer::rgb:
			tty << "RGB\n";
			break;
		case FrameBuffer::text:
			tty << "text\n";
			break;
	}

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
