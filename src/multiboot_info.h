#ifndef MULTIBOOT_INFO_H_
#define MULTIBOOT_INFO_H_

#include "common.h"
#include "multiboot2.h"

namespace multiboot {
	class Info {
	private:
		uint32_t magic, addr;
		int tag_num;
		bool acpi_new;
	public:
		struct tags_t {
			tag_string			*cmdline		= nullptr;
			tag_string			*bootloader		= nullptr;
			tag_module			*module			= nullptr;
			tag_basic_meminfo	*basic_meminfo	= nullptr;
			tag_bootdev			*bootdev		= nullptr;
			tag_mmap			*mmap			= nullptr;
			tag_vbe				*vbe			= nullptr;
			tag_framebuffer		*framebuffer	= nullptr;
			tag_elf_sections	*elf_sections	= nullptr;
			tag_apm				*apm			= nullptr;
			tag_efi32			*efi32			= nullptr;
			tag_efi64			*efi64			= nullptr;
			tag_smbios			*smbios			= nullptr;
			tag_acpi			*acpi			= nullptr;
			tag_network			*network		= nullptr;
			tag_efi_mmap		*efi_mmap		= nullptr;
			tag					*efi_bs			= nullptr;
			tag_efi32_ih		*efi32_ih		= nullptr;
			tag_efi64_ih		*efi64_ih		= nullptr;
			tag_load_base_addr	*load_base_addr	= nullptr;
		};
		tags_t tags;

		Info() : magic(0x00), addr(0x00), tag_num(0), acpi_new(false) {}
		void init(const uint32_t &m, const uint32_t &a){
			magic	= m;
			addr	= a;
			tag_num	= 0;
			parse_tags();
		}

		bool check_magic() const { return magic==bootloader_magic; }
		void parse_tags();

		int get_tag_num() const {	return tag_num; }
		const char* cmdline() const {	return tags.cmdline->string; }
		const char* bootloader()const{	return tags.bootloader->string; }
		auto vram_addr() const {	return (addr_t)tags.framebuffer->common.addr; }
		auto vram_width()const {	return tags.framebuffer->common.width;}
		auto vram_height()const{	return tags.framebuffer->common.height;}
		bool is_vram_text()const{	return tags.framebuffer->common.ftype == FrameBuffer::text; }
		bool is_acpi_new() const {		return acpi_new; }
	};
} // namespace multiboot

#endif
