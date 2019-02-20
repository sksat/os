#ifndef IDT_H_
#define IDT_H_

#include "common.h"
#include "asmfunc.h"

namespace IDT {
	struct Desc {
		struct Raw {
			Raw() : raw64(0x00) {}
			union {
				uint64_t raw64;
				struct {
					union {
						uint32_t low32;
						struct {
							uint16_t	offset_low;
							uint16_t	selector;
						};
					};
					union {
						uint32_t high32;
						struct {
							uint8_t		zero;
							uint8_t		type	: 4;
							bool		S		: 1;
							uint8_t		DPL		: 2;
							bool		P		: 1;
							uint16_t	offset_high;
						};
					};
				};
			};
		} __attribute__((__packed__));

		Raw raw;

		void offset(const uint32_t &o){
			raw.offset_low	= o & 0xffff;
			raw.offset_high	= (o >> 16) & 0xffff;
		}
		void selector(const uint16_t &s){
			raw.selector = s;
		}
	};

	extern uint32_t addr;
	extern uint16_t limit;

	extern Desc::Raw *IDT;

	inline void set_desc(const uint16_t &num, Desc desc){
		IDT = reinterpret_cast<Desc::Raw*>(addr);
		IDT[num] = desc.raw;
	}

	inline void load_idtr(){
		asmfunc::load_idtr(limit, static_cast<uint32_t>(addr));
	}

	void init();
}

#endif
