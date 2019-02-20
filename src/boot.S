#define ASM_FILE	1
#include "multiboot2.h"

#define ARCHITECTURE		MULTIBOOT_ARCHITECTURE_I386
#define HEADER_SIZE			(multiboot_header_end - multiboot_header)
#define HEADER_CHECKSUM		-(MULTIBOOT2_HEADER_MAGIC + ARCHITECTURE + HEADER_SIZE)

// C function call
#ifdef	HAVE_ASM_UNSCORE
	#define EXT_C(fn)		_ ## fn
#else
	#define EXT_C(fn)		fn
#endif

.intel_syntax noprefix

multiboot_header:
	.long	MULTIBOOT2_HEADER_MAGIC
	.long	MULTIBOOT_ARCHITECTURE_I386
	.long	HEADER_SIZE
	.long	HEADER_CHECKSUM

end_tag:
	.short	MULTIBOOT_HEADER_TAG_END
	.short	0
	.long	8
multiboot_header_end:

.global entry

.section .text
.code32

entry:
	cli
	// initialize stack
	mov		esp, initial_stack_buffer_end

	push	0
	popf			// reset EFLAGS

	push	ebx		// multiboot information structure
	push	eax		// magic value
	call	EXT_C(kmain)

loop:
	hlt
	jmp		loop
