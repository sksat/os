#include "common.h"
#include "multiboot_info.h"
#include "vram.h"
#include "tty.h"
#include "util.h"
#include "gdt.h"

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

	auto mmap = minfo->tags.mmap;
	int mmap_num = (mmap->size-sizeof(uint32_t)*4)/sizeof(multiboot::mmap_entry);
	tty << "mmap: size=" << mmap->size
		<< ", num=" << mmap_num
		<< ", version=" << mmap->entry_version
		<< "\n";

	for(int i=0;i<mmap_num;i++){
		auto& entry = mmap->entries[i];
		tty << "\t" << i << ": base addr=" << entry.addr
			<< ",\t\tlen=" << entry.len << "\t";
		switch(entry.type){
		using namespace multiboot;
		case Memory::Available:
			tty << "(available)";
			break;
		case Memory::Reserved:
			tty << "(reserved)";
			break;
		case Memory::AcpiReclaimable:
			tty << "(ACPI reclaimable)";
			break;
		case Memory::NVS:
			tty << "(NVS)";
			break;
		case Memory::BadRAM:
			tty << "(BAD)";
			break;
		}
		tty << "\n";
	}

	if(minfo->tags.vbe != nullptr)
		tty << "VBE" << "\n";

	if(minfo->tags.load_base_addr != nullptr)
		tty << "load base addr = "
			<< (uint64_t)minfo->tags.load_base_addr->addr << "\n";

	// GDT test
	{
		tty << "GDT test \n";
		GDT::addr = 0x10000;
		GDT::limit	= sizeof(GDT::Desc::Raw) * 3;

		tty << "base addr=" << (uint64_t)GDT::addr
			<< ", limit=" << (uint64_t)GDT::limit << "\n";

		tty << "\tselector null";
		GDT::Desc zero;
		zero.raw.raw64=0x00;
		GDT::set_desc(0, zero);
		tty << "\t[ok]\n";

		tty << "\tselector 1,2";
		GDT::Desc d1, d2;
		d1.base(0x00);
		d1.limit(0xffffffff);
		d2.base(0x00);
		d2.limit(0xffffffff);

		d1.config = GDT::Desc::Executable | GDT::Desc::ReadOnly;
		d2.config = GDT::Desc::Default;

		GDT::set_desc(1, d1);
		GDT::set_desc(2, d2);
		tty << "\t[ok]\n";

		tty << "\tload";
		GDT::load_gdtr();
		tty << "\t[ok]\n";
	}

	while(1);
	return;
}

extern "C" void __cxa_pure_virtual(){
	while(1);
}
