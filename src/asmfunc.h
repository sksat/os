#ifndef ASMFUNC_H_
#define ASMFUNC_H_

#ifndef ASM_FILE
#include <cstdint>

#define ASM extern "C"

namespace asmfunc {
	ASM uint32_t get_eip();

	ASM void cli();
	ASM void sti();
	ASM void hlt();

	ASM void load_gdtr(uint16_t limit, uint32_t addr);
	ASM void load_idtr(uint16_t limit, uint32_t addr);

	ASM uint8_t  in8(uint16_t port);
	ASM uint16_t in16(uint16_t port);
	ASM uint32_t in32(uint16_t port);
	ASM void out8(uint16_t port, uint8_t data);
	ASM void out16(uint16_t port, uint16_t data);
	ASM void out32(uint16_t port, uint32_t data);

	ASM void _int_handler_0x21();
}

#endif // ASM_FILE

#endif
