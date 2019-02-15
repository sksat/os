#include "multiboot_info.h"

using namespace multiboot;

void Info::parse_tags(){
	auto t = (tag*) (addr+8);

	for(;;){
		if(t->type == tag::End) break;

		tag_num++;

		switch(t->type){
			case tag::CmdLine:
				tags.cmdline = (tag_string*)t;
				break;
			case tag::BootLoaderName:
				tags.bootloader = (tag_string*)t;
				break;
			#define TAG(type) (tag_ ## type *)t
			case tag::Module:
				tags.module = TAG(module);
				break;
			case tag::BasicMemInfo:
				tags.basic_meminfo = TAG(basic_meminfo);
				break;
			case tag::BootDev:
				tags.bootdev = TAG(bootdev);
				break;
			case tag::MMap:
				tags.mmap = TAG(mmap);
				break;
			case tag::VBE:
				tags.vbe = TAG(vbe);
				break;
			case tag::FrameBuffer:
				tags.framebuffer = TAG(framebuffer);
				break;
			case tag::ELF_Sections:
				tags.elf_sections = TAG(elf_sections);
				break;
			case tag::APM:
				tags.apm = TAG(apm);
				break;
			case tag::EFI32:
				tags.efi32 = TAG(efi32);
				break;
			case tag::EFI64:
				tags.efi64 = TAG(efi64);
				break;
			case tag::SMBIOS:
				tags.smbios = TAG(smbios);
				break;
			case tag::ACPI_old:
			case tag::ACPI_new:
				tags.acpi = TAG(acpi);
				acpi_new = t->type == tag::ACPI_new;
				break;
			case tag::Network:
				tags.network = TAG(network);
				break;
			case tag::EFI_MMap:
				tags.efi_mmap = TAG(efi_mmap);
				break;
			case tag::EFI_BS:
				tags.efi_bs = t;
				break;
			case tag::EFI32_IH:
				tags.efi32_ih = TAG(efi32_ih);
				break;
			case tag::EFI64_IH:
				tags.efi64_ih = TAG(efi64_ih);
				break;
			case tag::LoadBaseAddr:
				tags.load_base_addr = TAG(load_base_addr);
				break;
			default:
				//TODO ERROR
				return;
		}

		t = (multiboot::tag*) ((uint8_t*)t + ((t->size+7)& ~7));
	}
};
