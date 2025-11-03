.section .text

// void *memset(void *dst, int value, size_t n)
.global memset
.type memset, %function
memset:
    cbz     x2, .ret
    mov     x9, x0

    uxtb    w3, w1
    mov     x4, x3
    orr     x4, x4, x4, lsl #8
    orr     x4, x4, x4, lsl #16
    orr     x4, x4, x4, lsl #32
    mov     x5, x4

    ands    x10, x0, #15
    cbz     x10, .dst_aligned

.align_dst_loop:
    strb    w3, [x0], #1
    subs    x2, x2, #1
    b.eq    .ret
    ands    x10, x0, #15
    b.ne    .align_dst_loop

.dst_aligned:
    cmp     x2, #16
    blt     .tail

.fill_16_loop:
    cmp     x2, #16
    blt     .tail
    stp     x4, x5, [x0], #16
    subs    x2, x2, #16
    b.ge    .fill_16_loop

//----------------------------------------
// Common tail handling (8/4/2/1 bytes)
//----------------------------------------
.tail:
    cbz     x2, .ret

    cmp     x2, #8
    blt     .tail4
    str     x4, [x0], #8
    subs    x2, x2, #8
    b.eq    .ret

.tail4:
    cmp     x2, #4
    blt     .tail2
    str     w3, [x0], #4
    subs    x2, x2, #4
    b.eq    .ret

.tail2:
    cmp     x2, #2
    blt     .tail1
    strh    w3, [x0], #2
    subs    x2, x2, #2
    b.eq    .ret

.tail1:
    cbz     x2, .ret
    strb    w3, [x0]

.ret:
    mov     x0, x9
    ret
