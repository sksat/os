/*  multiboot2.h - Multiboot 2 header file.  */
/*  Copyright (C) 1999,2003,2007,2008,2009,2010  Free Software Foundation, Inc.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ANY
 *  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MULTIBOOT_HEADER
#define MULTIBOOT_HEADER 1

/* How many bytes from the start of the file we search for the header.  */
#define MULTIBOOT_SEARCH			32768
#define MULTIBOOT_HEADER_ALIGN			8

/* The magic field should contain this.  */
#define MULTIBOOT2_HEADER_MAGIC			0xe85250d6

/* This should be in %eax.  */
#define MULTIBOOT2_BOOTLOADER_MAGIC		0x36d76289

/* Alignment of multiboot modules.  */
#define MULTIBOOT_MOD_ALIGN			0x00001000

/* Alignment of the multiboot info structure.  */
#define MULTIBOOT_INFO_ALIGN			0x00000008

/* Flags set in the 'flags' member of the multiboot header.  */

#define MULTIBOOT_TAG_ALIGN                  8
#define MULTIBOOT_TAG_TYPE_END               0
#define MULTIBOOT_TAG_TYPE_CMDLINE           1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME  2
#define MULTIBOOT_TAG_TYPE_MODULE            3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO     4
#define MULTIBOOT_TAG_TYPE_BOOTDEV           5
#define MULTIBOOT_TAG_TYPE_MMAP              6
#define MULTIBOOT_TAG_TYPE_VBE               7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER       8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS      9
#define MULTIBOOT_TAG_TYPE_APM               10
#define MULTIBOOT_TAG_TYPE_EFI32             11
#define MULTIBOOT_TAG_TYPE_EFI64             12
#define MULTIBOOT_TAG_TYPE_SMBIOS            13
#define MULTIBOOT_TAG_TYPE_ACPI_OLD          14
#define MULTIBOOT_TAG_TYPE_ACPI_NEW          15
#define MULTIBOOT_TAG_TYPE_NETWORK           16
#define MULTIBOOT_TAG_TYPE_EFI_MMAP          17
#define MULTIBOOT_TAG_TYPE_EFI_BS            18
#define MULTIBOOT_TAG_TYPE_EFI32_IH          19
#define MULTIBOOT_TAG_TYPE_EFI64_IH          20
#define MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR    21

#define MULTIBOOT_HEADER_TAG_END  0
#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST  1
#define MULTIBOOT_HEADER_TAG_ADDRESS  2
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS  3
#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS  4
#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER  5
#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN  6
#define MULTIBOOT_HEADER_TAG_EFI_BS        7
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32  8
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64  9
#define MULTIBOOT_HEADER_TAG_RELOCATABLE  10

#define MULTIBOOT_ARCHITECTURE_I386  0
#define MULTIBOOT_ARCHITECTURE_MIPS32  4
#define MULTIBOOT_HEADER_TAG_OPTIONAL 1

#define MULTIBOOT_LOAD_PREFERENCE_NONE 0
#define MULTIBOOT_LOAD_PREFERENCE_LOW 1
#define MULTIBOOT_LOAD_PREFERENCE_HIGH 2

#define MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED 1
#define MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED 2

#ifndef ASM_FILE

namespace multiboot {
	// types
	using uint8_t	= unsigned char;
	using uint16_t	= unsigned short;
	using uint32_t	= unsigned int;
	using uint64_t	= unsigned long long;

	constexpr uint32_t bootloader_magic = MULTIBOOT2_BOOTLOADER_MAGIC;

	// struct

	struct header {
		uint32_t magic;
		uint32_t arch;
		uint32_t header_length;
		uint32_t checksum;
	};

	struct header_tag {
		enum type_t : uint16_t {
			End = MULTIBOOT_HEADER_TAG_END,
			InfomationRequest,
			Address,
			EntryAddress,
			ConsoleFlags,
			FrameBuffer,
			ModuleAlign,
			EFI_BS,
			EntryAddressEFI32,
			EntryAddressEFI64,
			Relocatable,
		};

		type_t type;
		uint16_t flags;
		uint32_t size;
		struct infomation_request {
			uint16_t type;
			uint16_t flags;
			uint32_t size;
			uint32_t requests[0];
		};

		struct addr {
			uint16_t type;
			uint16_t flags;
			uint32_t size;
			uint32_t header_addr;
			uint32_t load_addr;
			uint32_t load_end_addr;
			uint32_t bss_end_addr;
		};

		struct entry_addr {
			uint16_t type;
			uint16_t flags;
			uint32_t size;
			uint32_t addr;
		};

		struct console_flags {
			uint16_t type;
			uint16_t flags;
			uint32_t size;
			uint32_t console_flags;
		};

		struct framebuffer {
			uint16_t type;
			uint16_t flags;
			uint32_t size;
			uint32_t width;
			uint32_t height;
			uint32_t depth;
		};

		struct module_align {
			uint16_t type;
			uint16_t flags;
			uint32_t size;
		};

		struct relocatable {
			uint16_t type;
			uint16_t flags;
			uint32_t size;
			uint32_t min_addr;
			uint32_t max_addr;
			uint32_t align;
			uint32_t preference;
		};
	}; // multiboot::header_tag

	struct color {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};

#define MULTIBOOT_MEMORY_AVAILABLE			1
#define MULTIBOOT_MEMORY_RESERVED			2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE	3
#define MULTIBOOT_MEMORY_NVS				4
#define MULTIBOOT_MEMORY_BADRAM				5

	enum class Memory : uint32_t {
		Available = MULTIBOOT_MEMORY_AVAILABLE,
		Reserved,
		AcpiReclaimable,
		NVS,
		BadRAM,
	};

	struct mmap_entry {
		uint64_t addr;
		uint64_t len;
		Memory type; // uint32_t
		uint32_t zero;
	};

	using memory_map_t = mmap_entry;

	// tags

	struct tag {
		enum type_t : uint32_t {
			End = MULTIBOOT_TAG_TYPE_END,
			CmdLine,
			BootLoaderName,
			Module,
			BasicMemInfo,
			BootDev,
			MMap,
			VBE,
			FrameBuffer,
			ELF_Sections,
			APM,
			EFI32,
			EFI64,
			SMBIOS,
			ACPI_old,
			ACPI_new,
			Network,
			EFI_MMap,
			EFI_BS,
			EFI32_IH,
			EFI64_IH,
			LoadBaseAddr,
		};
		type_t type;
		uint32_t size;
	};

	struct tag_string {
		uint32_t type;
		uint32_t size;
		char string[0];
	};

	struct tag_module {
		uint32_t type;
		uint32_t size;
		uint32_t mod_start;
		uint32_t mod_end;
		char cmdline[0];
	};

	struct tag_basic_meminfo {
		uint32_t type;
		uint32_t size;
		uint32_t lower;
		uint32_t upper;
	};

	struct tag_bootdev {
		uint32_t type;
		uint32_t size;
		uint32_t biosdev;
		uint32_t slice;
		uint32_t part;
	};

	struct tag_mmap {
		uint32_t type;
		uint32_t size;
		uint32_t entry_size;
		uint32_t entry_version;
		mmap_entry entries[0];
	};

	struct tag_vbe {
		uint32_t type;
		uint32_t size;

		uint16_t mode;
		uint16_t interface_seg;
		uint16_t interface_off;
		uint16_t interface_len;

		struct info_block {
			uint8_t external_specification[512];
		};

		info_block control_info;

		struct mode_info_block {
			uint8_t external_specification[256];
		};

		mode_info_block mode_info;
	};

#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED	0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB		1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT	2

	enum class FrameBuffer : uint8_t {
		indexed	= MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED,
		rgb,
		ega_text,
		text = ega_text,
	};

	struct tag_framebuffer {
		struct common_info {
			uint32_t type;
			uint32_t size;

			uint64_t addr;
			uint32_t pitch;
			uint32_t width;
			uint32_t height;
			uint8_t  bpp;
			FrameBuffer ftype; // uint8_t
			uint16_t reserved;
		};

		common_info common;

		union {
			struct {
				uint16_t palette_num_colors;
				color palette[0];
			};

			struct {
				uint8_t red_field_pos;
				uint8_t red_mask_size;
				uint8_t green_field_pos;
				uint8_t green_mask_size;
				uint8_t blue_field_pos;
				uint8_t blue_mask_size;
			};
		};
	}; // tag_framebuffer

	struct tag_elf_sections {
		uint32_t type;
		uint32_t size;
		uint32_t num;
		uint32_t entsize;
		uint32_t shndx;
		char sections[0];
	};

	struct tag_apm {
		uint32_t type;
		uint32_t size;
		uint16_t version;
		uint16_t cseg;
		uint32_t offset;
		uint16_t cseg_16;
		uint16_t dseg;
		uint16_t flags;
		uint16_t cseg_len;
		uint16_t cseg_16_len;
		uint16_t dseg_len;
	};

	struct tag_efi32 {
		uint32_t type;
		uint32_t size;
		uint32_t pointer;
	};

	struct tag_efi64 {
		uint32_t type;
		uint32_t size;
		uint64_t pointer;
	};

	struct tag_smbios {
		uint32_t type;
		uint32_t size;
		uint8_t major;
		uint8_t minor;
		uint8_t reserved[6];
		uint8_t tables[0];
	};

	struct tag_acpi { // tag_old_acpi,tag_new_acpi
		uint32_t type;
		uint32_t size;
		uint8_t rsdp[0];
	};

	struct tag_network {
		uint32_t type;
		uint32_t size;
		uint8_t dhcpack[0];
	};

	struct tag_efi_mmap {
		uint32_t type;
		uint32_t size;
		uint32_t descr_size;
		uint32_t descr_vers;
		uint8_t efi_mmap[0];
	};

	struct tag_efi32_ih {
		uint32_t type;
		uint32_t size;
		uint32_t pointer;
	};

	struct tag_efi64_ih {
		uint32_t type;
		uint32_t size;
		uint64_t pointer;
	};

	struct tag_load_base_addr {
		uint32_t type;
		uint32_t size;
		uint32_t addr;
	};

} // namespace multiboot

#endif /* ! ASM_FILE */

#endif /* ! MULTIBOOT_HEADER */
