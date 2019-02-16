#ifndef GDT_H_
#define GDT_H_

#include "common.h"
#include "asmfunc.h"

namespace GDT {
	// GDTR
	inline uint16_t limit	= 0x00;
	inline uint32_t addr	= 0x00;

	// descriptor
	struct Desc {
		Desc(){}

		struct Raw {
			Raw() : low32(0x00000000),
					base_mid(0), type(0x00), S(1), DPL(0), P(1),
					limit_high(0x00), AVL(0), D_B(1), G(0), base_high(0x00) {}
			union {
				uint64_t raw64;
				struct {
					union {
						uint32_t low32;
						struct {
							uint16_t	limit_low;
							uint16_t	base_low;
						};
					};

					union {
						uint32_t high32;
						struct {
							uint8_t		base_mid;
							uint8_t		type		: 4; // segment type
							bool		S			: 1; // descriptor type flag(0=system 1=code,data)
							uint8_t		DPL			: 2; // descriptor priviledge level
							bool		P			: 1; // segment present flag(1)
							uint8_t		limit_high	: 4;
							bool		AVL			: 1; // available flag(free)
							bool					: 1;
							bool		D_B			: 1; // D/B (0=16bit, 1=32bit)
							bool		G			: 1; // granularity flag(0=byte, 1=4Kbyte)
							uint8_t		base_high;
						};
					};
				};
			};
		} __attribute__((__packed__));
		Raw raw;

		enum Config : uint16_t {
			// raw.type
			Access		= 0b0000000001,
			ReadOnly	= 0b0000000010,
			DirectDown	= 0b0000000100,
			Conforming	= 0b0000001000,
			Executable	= 0b0000010000,
			// raw.S
			System		= 0b0000100000,
			// raw.P
			NotPresent	= 0b0001000000,
			// raw.AVL
			Available	= 0b0010000000,
			// raw.D_B
			Bit16		= 0b0100000000,
			G			= 0b1000000000,
			Default		= 0b0000000000,
		};
		uint16_t config;

		void limit(uint32_t l){
			if(l > 0xfffff){
				config |= G;
				update_config();
				l /= 0x1000;
			}
			raw.limit_low	= l & 0xffff;
			raw.limit_high	= (l >> 16) & 0x0f;
		}
		void base(const uint32_t &b){
			raw.base_low	= b & 0xffff;
			raw.base_mid	= (b >> 16) & 0xff;
			raw.base_high	= (b >> 24) & 0xff;
		}
		void ring(const uint8_t &r){
			raw.DPL = r;
		}

		void update_config();
	};

	// GDT
	inline Desc::Raw *GDT = nullptr;

	inline void set_desc(const uint16_t &num, Desc &desc){
		desc.update_config();
		GDT = (Desc::Raw*) addr;
		GDT[num] = desc.raw;
	}

	inline void load_gdtr(){
		asmfunc::load_gdtr(limit, addr);
	}
	inline void load_gdtr(const uint16_t limit, const uint32_t addr){
		GDT::limit	= limit;
		GDT::addr	= addr;
		load_gdtr(limit, addr);
	}
}

#endif
