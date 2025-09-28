.global _start
.section .text

_start:
    mrs x0, CurrentEL
    cmp x0, #0x03
    bne el2
    eret
el2:
    cmp x0, #0x02
    bne el1
    eret
el1:
    ldr x30, =stack_top
    mov SP, X30
    bl main
    b .

.section .data
