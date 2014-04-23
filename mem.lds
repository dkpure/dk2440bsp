OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS {
	. = 0x33E00000;

	. = ALIGN(4);
	.text :
	{
		core_init.o (.text)
		*(.text)
	}

	. = ALIGN(4);
	.dara :
	{
		*(.data)
	}

	. = ALIGN(4);
	bss_start = .;
	.bss :
	{
		*(.bss)
	}
	bss_end = .;
}
