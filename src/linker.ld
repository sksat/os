ENTRY(entry)

SECTIONS {
	. = 1M;
	.text :
	{
		*(.text)
	}
}
