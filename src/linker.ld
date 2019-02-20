STACK_SIZE = 0x4000; /* 16KB */

ENTRY(entry)

SECTIONS {
	. = 0x100000;

	.text : {
		*(.text)
	}

	.rodata : {
		*(.rodata)
	}

	.data : {
		*(.data)
	}

	.bss : {
		*(.bss)
		initial_stack_buffer = .;
		. += STACK_SIZE;
		initial_stack_buffer_end = .;
	}
}
