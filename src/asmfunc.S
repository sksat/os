#define ASM_FILE
#include "asmfunc.h"

.global	get_eip

.global cli, sti, hlt

.global load_gdtr, load_idtr

.global in8, in16, in32
.global out8, out16, out32

.global _int_handler_0x21

.intel_syntax noprefix

.section .text
.code32

get_eip:
	mov		eax, [esp]
	ret

cli:
	cli
	ret

sti:
	sti
	ret

hlt:
	hlt
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

load_idtr:
	mov		ax, [esp+4]
	mov		[esp+6], ax
	lidt	[esp+6]
	ret

in8:	// u8 in8(u16 port)
	mov		dx, [esp+4]
	mov		eax, 0
	in		al, dx
	ret

in16:	// u16 in16(u16 port)
	mov		dx, [esp+4]
	mov		eax, 0
	in		ax, dx
	ret

in32:	// u32 in32(u16 port)
	mov		dx, [esp+4]
	mov		eax, 0
	in		eax, dx
	ret

out8:	// void out8(u16 port, u8 data)
	mov		dx, [esp+4]
	mov		al, [esp+8]
	out		dx, al
	ret

out16:	// void out16(u16 port, u16 data)
	mov		dx, [esp+4]
	mov		ax, [esp+8]
	out		dx, ax
	ret

out32:	// void out32(u16 port, u32 data)
	mov		dx, [esp+4]
	mov		eax, [esp+8]
	out		dx, eax
	ret

.extern int_handler21
_int_handler_0x21:
	push	es
	push	ds
	pushad
	mov		eax, esp
	push	eax
	mov		ax, ss
	mov		ds, ax
	mov		es, ax
	call	int_handler21
	pop		eax
	popad
	pop		ds
	pop		es
	iretd
