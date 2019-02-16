#include "gdt.h"

using namespace GDT;

void Desc::update_config(){
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
