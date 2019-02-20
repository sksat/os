#define ASM_FILE
#include "asmfunc.h"

	.global	get_eip
	.global load_gdtr

.intel_syntax noprefix

.section .text
.code32

get_eip:
	mov		eax, [esp]
	ret

load_gdtr:
	mov		ax,	[esp+4]
	mov		[esp+6], ax
	lgdt	[esp+6]
	ljmp	0x08:_load_gdtr_flush // code=0x08
_load_gdtr_flush:
	mov		ax, 0x10 // data=0x10
	mov		ds, ax
	mov		es, ax
	mov		fs, ax
	mov		gs, ax
	mov		ss, ax
	ret
