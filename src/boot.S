#define MULTIBOOT2_HEADER_MAGIC			0xe85250d6
#define MULTIBOOT_ARCHITECTURE_I386		0
#define MULTIBOOT_HEADER_TAG_END		0

#define ARCHITECTURE		MULTIBOOT_ARCHITECTURE_I386

#define HEADER_SIZE			(multiboot_header_end - multiboot_header)
#define HEADER_CHECKSUM		-(MULTIBOOT2_HEADER_MAGIC + ARCHITECTURE + HEADER_SIZE)

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
	mov dword ptr [0xb8000], 0x2f4b2f4f
	hlt
