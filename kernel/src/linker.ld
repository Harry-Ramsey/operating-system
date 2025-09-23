ENTRY(_start)
SECTIONS {
    . = 0x0000000040000000;
    .text : {
        boot_s.o(.text)
        main_c.o(.text)
        *(.text)
    }
    .data : { *(.data) }
    .bss : { *(.bss) }
    . = ALIGN(16);
    . = . + 0x1000;
    stack_top = .;
}
