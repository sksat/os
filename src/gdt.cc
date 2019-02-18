#include "gdt.h"

namespace GDT {
	uint32_t addr	= 0x00000000;
	uint16_t limit	= 0x0000;
	Desc::Raw *GDT	= nullptr;
}

void GDT::Desc::update_config(){
	uint8_t type = 0b0000;
	if(config & Access)		// bit40
		type |= 0b0001;
	if(config & ReadOnly)	// bit41
		type |= 0b0010;
	if(config & Executable){ // code segment
		type |= 0b1000;
		if(config & Conforming)
			type |= 0b0100;
	}else if(config & DirectDown)
		type |= 0b0100;

	raw.type = type;

	if(config & System)
		raw.S = 1;
	if(config & NotPresent)
		raw.P = 0;
	if(config & Available)
		raw.AVL = 1;
	if(config & Bit16)
		raw.D_B = 0;
	if(config & G)
		raw.G = 1;
}

void GDT::init(){
	addr	= 0x10000;
	limit	= sizeof(Desc::Raw) * 3;

	Desc null, kcode, kdata;
	null = Desc();
	kcode= Desc();
	kdata= Desc();
	null.raw.raw64 = 0x00;

	kcode.base(0x00);
	kcode.limit(0xffffffff);
	kcode.config = Desc::Executable | Desc::ReadOnly;

	kdata.base(0x00);
	kdata.limit(0xffffffff);
	kdata.config = Desc::Default;

	null.update_config();
	kcode.update_config();
	kdata.update_config();

	set_desc(0, null);
	set_desc(1, kcode);
	set_desc(2, kdata);

	load_gdtr();
}
