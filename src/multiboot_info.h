#ifndef MULTIBOOT_INFO_H_
#define MULTIBOOT_INFO_H_

#include "multiboot2.h"

namespace multiboot {
	class Info {
	private:
		uint32_t magic, addr;
		int tag_num;
		bool acpi_new;
	public:
		struct tags_t {
			tag_string			*cmdline;
			tag_string			*bootloader;
			tag_module			*module;
			tag_basic_meminfo	*basic_meminfo;
			tag_bootdev			*bootdev;
			tag_mmap			*mmap;
			tag_vbe				*vbe;
			tag_framebuffer		*framebuffer;
			tag_elf_sections	*elf_sections;
			tag_apm				*apm;
			tag_efi32			*efi32;
			tag_efi64			*efi64;
			tag_smbios			*smbios;
			tag_acpi			*acpi;
			tag_network			*network;
			tag_efi_mmap		*efi_mmap;
			tag					*efi_bs;
			tag_efi32_ih		*efi32_ih;
			tag_efi64_ih		*efi64_ih;
			tag_load_base_addr	*load_base_addr;
		};
		tags_t tags;

		Info(const uint32_t &m, const uint32_t &a) : magic(m), addr(a), tag_num(0), acpi_new(false) {}

		bool check_magic() const { return magic==bootloader_magic; }
		void parse_tags();

		int get_tag_num() const {	return tag_num; }
		const char* cmdline() const {	return tags.cmdline->string; }
		const char* bootloader()const{	return tags.bootloader->string; }
		bool is_acpi_new() const {		return acpi_new; }
	};
} // namespace multiboot

#endif
