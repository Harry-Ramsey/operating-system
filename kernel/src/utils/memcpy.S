.section .text

// void *memcpy(void *dst, const void *src, size_t n)
.global memcpy
.type memcpy, %function
memcpy:
    cbz     x2, .ret
    mov     x9, x0

    // Check if dest and src can be aligned to 16-bytes
    eor     x10, x0, x1
    ands    x10, x10, #15
    b.ne    .align_dst_only

    ands    x11, x0, #15
    cbz     x11, .aligned_both

.align_both_loop:
    ldrb    w12, [x1], #1
    strb    w12, [x0], #1
    subs    x2, x2, #1
    b.eq    .ret
    ands    x11, x0, #15
    b.ne    .align_both_loop

.aligned_both:
.copy_16_loop:
    cmp     x2, #16
    blt     .tail
    ldp     x12, x13, [x1], #16
    stp     x12, x13, [x0], #16
    subs    x2, x2, #16
    b.ge    .copy_16_loop
    b       .tail

.align_dst_only:
    ands    x11, x0, #15
    cbz     x11, .aligned_dst

.align_dst_loop:
    ldrb    w12, [x1], #1
    strb    w12, [x0], #1
    subs    x2, x2, #1
    b.eq    .ret
    ands    x11, x0, #15
    b.ne    .align_dst_loop

.aligned_dst:
.copy_8_loop:
    cmp     x2, #8
    blt     .tail
    ldr     x12, [x1], #8
    str     x12, [x0], #8
    subs    x2, x2, #8
    b.ge    .copy_8_loop

//----------------------------------------
// Common tail: 8 / 4 / 2 / 1-byte copies
//----------------------------------------
.tail:
    cbz     x2, .ret
    cmp     x2, #8
    blt     .tail4
    ldr     x12, [x1], #8
    str     x12, [x0], #8
    subs    x2, x2, #8
    b.eq    .ret

.tail4:
    cmp     x2, #4
    blt     .tail2
    ldr     w12, [x1], #4
    str     w12, [x0], #4
    subs    x2, x2, #4
    b.eq    .ret

.tail2:
    cmp     x2, #2
    blt     .tail1
    ldrh    w12, [x1], #2
    strh    w12, [x0], #2
    subs    x2, x2, #2
    b.eq    .ret

.tail1:
    cbz     x2, .ret
    ldrb    w12, [x1]
    strb    w12, [x0]

.ret:
    mov     x0, x9
    ret
