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
    . = ALIGN(0x1000);    /* ensure the current location is 4KB aligned */
    l1_table = .;
    . = . + 0x1000;       /* reserve one page for L1 table */
    stack_top = .;
}
