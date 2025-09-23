.global _start
.section .text

_start:
    ldr x30, =_stack_top
    mov SP, X30
    bl main
    b .

.section .data
