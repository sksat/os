#ifndef PIC_H_
#define PIC_H_

#include "common.h"

namespace PIC {
	enum port : uint16_t {
		pic0_cmd	= 0x20,
		pic0_data	= 0x21,
		pic1_cmd	= 0xa0,
		pic1_data	= 0xa1,
	};

	enum IRQ : uint16_t {
		#define _IRQ(n) IRQ ## n = (1 << n)
		_IRQ(0),
		_IRQ(1),
		_IRQ(2),
		_IRQ(3),
		_IRQ(4),
		_IRQ(5),
		_IRQ(6),
		_IRQ(7),
		_IRQ(8),
		_IRQ(9),
		_IRQ(10),
		_IRQ(11),
		_IRQ(12),
		_IRQ(13),
		_IRQ(14),
		_IRQ(15),
		#undef _IRQ
	};

	void init();

	void disable_all_int();
	void set_mask(uint16_t mask);
}

#endif
