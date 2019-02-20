#ifndef ASMFUNC_H_
#define ASMFUNC_H_

#ifndef ASM_FILE
#include <cstdint>

#define ASM extern "C"

namespace asmfunc {
	ASM uint32_t get_eip();
	ASM void load_gdtr(uint16_t limit, uint32_t addr);
	ASM void load_idtr(uint16_t limit, uint32_t addr);
}

#endif // ASM_FILE

#endif
