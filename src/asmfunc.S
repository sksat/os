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
	ret
