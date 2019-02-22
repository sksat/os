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

	d.selector(1 * 8);
	d.raw.type	= 0xe;
	d.raw.S		= false;
	d.raw.DPL	= 0;
	d.raw.P		= true;

#define SET(num) \
	d.offset(reinterpret_cast<uint32_t>(asmfunc::_int_handler_ ## num )); \
	set_desc(num, d);

	SET(0x21);
}
