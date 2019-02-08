ISO		= os.iso

IMG_DIR	= image
BOOT_DIR= $(IMG_DIR)/boot
GRUB_DIR= $(IMG_DIR)/boot/grub

QEMU=qemu-system-x86_64

# command

default: iso

build:
	make -C src

iso: $(ISO)

run: $(ISO)
	$(QEMU) -drive format=raw,file=$(ISO)

clean:
	rm -f $(ISO)
	rm -rf $(IMG_DIR)
	make -C src clean

$(ISO):
	make build
	mkdir -p $(GRUB_DIR)
	cp grub.cfg $(GRUB_DIR)
	cp src/kernel.bin $(BOOT_DIR)
	grub-mkrescue -o $(ISO) $(IMG_DIR)
