#define ASM_FILE	1
#include "multiboot2.h"

#define ARCHITECTURE		MULTIBOOT_ARCHITECTURE_I386
#define HEADER_SIZE			(multiboot_header_end - multiboot_header)
#define HEADER_CHECKSUM		-(MULTIBOOT2_HEADER_MAGIC + ARCHITECTURE + HEADER_SIZE)

// size of stack (16KB)
#define STACK_SIZE			0x4000

// C function call
#ifdef	HAVE_ASM_UNSCORE
	#define EXT_C(fn)		_ ## fn
#else
	#define EXT_C(fn)		fn
#endif

multiboot_header:
	.long	MULTIBOOT2_HEADER_MAGIC
	.long	MULTIBOOT_ARCHITECTURE_I386
	.long	HEADER_SIZE
	.long	HEADER_CHECKSUM
	.short	MULTIBOOT_HEADER_TAG_END
	.short	0
	.long	8
multiboot_header_end:

.intel_syntax noprefix
.global entry

.section .text
.code32

entry:
	mov		esp, stack+STACK_SIZE	// initialize stack

	push	0
	popf			// reset EFLAGS

	push	ebx		// multiboot information structure
	push	eax		// magic value
	call	EXT_C(kmain)

	mov		dword ptr [0xb8000], 0x2f4b2f4b		// puts("OK")

loop:
	hlt
	jmp		loop

halt_message:
	.asciz	"Halted."

// stack
	.comm	stack, STACK_SIZE
