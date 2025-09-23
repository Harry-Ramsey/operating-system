ENTRY(_start)
SECTIONS
{
    /* Load address where kernel is placed by the bootloader */
    . = 0x0000000040000000;

    /* --- Code section --- */
    .text : ALIGN(4K) {
        *(.text.boot)    /* optional if you have a boot.S */
        *(.text)
        *(.rodata*)      /* const data and strings */
    }

    /* --- Initialized data --- */
    .data : ALIGN(4K) {
        *(.data)
    }

    /* --- Uninitialized data --- */
    .bss : ALIGN(4K) {
        *(.bss)
        *(COMMON)
    }

    /* --- Stack (grows downward) --- */
    . = ALIGN(4K);
    _stack_bottom = .;
    . = . + 0x1000;     /* 4KB stack */
    _stack_top = .;

    /* --- End of kernel image --- */
    _end = .;
}
