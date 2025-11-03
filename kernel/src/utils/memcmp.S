.section .text

// int memcmp(const void *s1, const void *s2, size_t n)
// Return: 0 if equal, -1 if s1 < s2, 1 if s1 > s2
.global memcmp
.type memcmp, %function
memcmp:
    cbz x2, .ret_eq               // if n == 0

    // Align x0 and x1 where possible
    eor x11, x0, x1
    and x11, x11, #15
    cbz x11, .loop16

.align:
    and x11, x0, #15
    cbz x11, .loop16
    ldrb w9, [x0], #1
    ldrb w10, [x1], #1
    cmp w9, w10
    b.ne .ret
    subs x2, x2, #1
    b.eq .ret_eq
    b .align

.loop16:
    cmp x2, #16
    b.lt .tail8
    ldp x9, x11, [x0], #16
    ldp x10, x12, [x1], #16
    cmp x9, x10
    b.ne .ret
    cmp x11, x12
    b.ne .ret
    subs x2, x2, #16
    b.gt .loop16

.tail8:
    cmp x2, #8
    b.lt .tail4
    ldr x9, [x0], #8
    ldr x10, [x1], #8
    cmp x9, x10
    b.ne .ret
    subs x2, x2, #8

.tail4:
    cmp x2, #4
    b.lt .tail2
    ldr w9, [x0], #4
    ldr w10, [x1], #4
    cmp w9, w10
    b.ne .ret
    subs x2, x2, #4

.tail2:
    cmp x2, #2
    b.lt .tail1
    ldrh w9, [x0], #2
    ldrh w10, [x1], #2
    cmp w9, w10
    b.ne .ret
    subs x2, x2, #2

.tail1:
    cbz x2, .ret_eq
    ldrb w9, [x0]
    ldrb w10, [x1]
    cmp w9, w10
    b.eq .ret_eq

.ret:
    cmp x9, x10
.ret_eq:
    cset x0, ne
    cneg x0, x0, lo
    ret
