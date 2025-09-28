.global _vector_table_el1
.section .text

.macro context_save
    stp x28, x29, [sp, #-16]!
    stp x26, x27, [sp, #-16]!
    stp x24, x25, [sp, #-16]!
    stp x22, x23, [sp, #-16]!
    stp x20, x21, [sp, #-16]!
    stp x18, x19, [sp, #-16]!
    stp x16, x17, [sp, #-16]!
    stp x14, x15, [sp, #-16]!
    stp x12, x13, [sp, #-16]!
    stp x10, x11, [sp, #-16]!
    stp x8, x9, [sp, #-16]!
    stp x6, x7, [sp, #-16]!
    stp x4, x5, [sp, #-16]!
    stp x2, x3, [sp, #-16]!
    stp x0, x1, [sp, #-16]!
.endm

.macro context_restore
    ldp x0, x1, [sp], #16
    ldp x2, x3, [sp], #16
    ldp x4, x5, [sp], #16
    ldp x6, x7, [sp], #16
    ldp x8, x9, [sp], #16
    ldp x10, x11, [sp], #16
    ldp x12, x13, [sp], #16
    ldp x14, x15, [sp], #16
    ldp x16, x17, [sp], #16
    ldp x18, x19, [sp], #16
    ldp x20, x21, [sp], #16
    ldp x22, x23, [sp], #16
    ldp x24, x25, [sp], #16
    ldp x26, x27, [sp], #16
    ldp x28, x29, [sp], #16
.endm

.macro vector_entry handler
    .balign 0x80
    context_save
    bl \handler
    context_restore
    eret
.endm

.extern exception_not_implemented

.balign 0x800
_vector_table_el1:
current_el_sp0_sync:
    vector_entry exception_not_implemented
current_el_sp0_irq:
    vector_entry exception_not_implemented
current_el_sp0_fiq:
    vector_entry exception_not_implemented
current_el_sp0_serror:
    vector_entry exception_not_implemented

current_el_spx_sync:
    vector_entry exception_not_implemented
current_el_spx_irq:
    vector_entry exception_not_implemented
current_el_spx_fiq:
    vector_entry exception_not_implemented
current_el_spx_serror:
    vector_entry exception_not_implemented

lower_el_aarch64_sync:
    vector_entry exception_not_implemented
lower_el_aarch64_irq:
    vector_entry exception_not_implemented
lower_el_aarch64_fiq:
    vector_entry exception_not_implemented
lower_el_aarch64_serror:
    vector_entry exception_not_implemented

lower_el_aarch32_sync:
    vector_entry exception_not_implemented
lower_el_aarch32_irq:
    vector_entry exception_not_implemented
lower_el_aarch32_fiq:
    vector_entry exception_not_implemented
lower_el_aarch32_serror:
    vector_entry exception_not_implemented

