.global _start
.section .text

_start:
    mrs x0, CurrentEL
    cmp x0, #(0x03 << 2)
    bne el2_entry
    adr x0, el1_entry
    msr elr_el3, x0
    eret
el2_entry:
    cmp x0, #(0x02 << 2)
    bne el1_entry
    adr x0, el1_entry
    msr elr_el2, x0
    eret
el1_entry:
    ldr x30, =_stack_top
    mov SP, X30
    bl main
    b .

.section .data
