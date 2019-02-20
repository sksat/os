#include "idt.h"
#include "gdt.h"

namespace IDT {
	uint32_t addr	= 0x00000000;
	uint16_t limit	= 0x0000;
	Desc::Raw *IDT	= nullptr;
}

void IDT::init(){
	addr	= GDT::addr + GDT::limit;
	limit	= sizeof(Desc::Raw) * 0xff;

	Desc d;
	for(auto i=0;i<0xff;i++)
		set_desc(i, d);

	load_idtr();
}
