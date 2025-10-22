.global _start
.section .text

.extern _vector_table_el1

.equ TT_S1_DEVICE_nGnRnE,   0x00600000000000409
.equ TT_S1_NORMAL_WBWA,     0x00000000000000405

_start:
    mrs x0, CurrentEL
    cmp x0, #(0x03 << 2)
    bne el2_entry

    // Disable trapping CPTR EL3, EL2 and EL1
    mov x0, #0x0
    msr cptr_el3, x0
    msr cptr_el2, x0
    msr cpacr_el1, x0

    // Configure SCR_EL3
    mov x0, #(1 << 0)       // NS = 1 (Non-secure)
    orr x0, x0, #(1 << 10)  // RW = 1 (AArch64 for next EL)
    orr x0, x0, #(1 << 1)   // IRQ = 1 (EL1 IRQs routed to EL1)
    orr x0, x0, #(1 << 2)   // FIQ = 1
    msr scr_el3, x0

    ldr x0, =_vector_table_el1
    msr vbar_el3, x0

    // Disable HCR_EL2
    mov x0, #(1 << 31)
    msr hcr_el2, x0

    // Setup VMPIDR_EL2/VPIDR_EL1
    mrs x0, MIDR_EL1
    msr vpidr_el2, x0
    mrs x0, MPIDR_EL1
    msr vmpidr_el2, x0

    // Set VMID
    msr vttbr_el2, xzr

    // Set SCTLRs for EL2/1 to safe values
    msr sctlr_el2, xzr
    msr sctlr_el1, xzr

    // Prepare to return to EL1 code
    adr x0, el1_entry
    msr elr_el3, x0

    // Prepare to drop into EL1 execution
    mov x0, #5
    msr spsr_el3, x0
    eret
el2_entry:
    cmp x0, #(0x02 << 2)
    bne el1_entry
    adr x0, el1_entry
    msr elr_el2, x0
    eret
el1_entry:
    ldr x1, =_vector_table_el1
    msr vbar_el1, x1

    ldr x0, =_el1_l0_table
    msr ttbr0_el1, x0

    // Setup attributes for translation table
    // Attr1: Device memory
    // Attr2: DRAM
    mov x0, #0xFF00
    msr mair_el1, x0

    mov      x0, #0x19                        // T0SZ=0b011001 Limits VA space to 39 bits, translation starts @ l1
    orr      x0, x0, #(0x1 << 8)              // IGRN0=0b01    Walks to TTBR0 are Inner WB/WA
    orr      x0, x0, #(0x1 << 10)             // OGRN0=0b01    Walks to TTBR0 are Outer WB/WA
    orr      x0, x0, #(0x3 << 12)             // SH0=0b11      Inner Shareable
    orr      x0, x0, #(0x1 << 23)             // EPD1=0b1      Disable table walks from TTBR1
                                            // TBI0=0b0
                                            // TG0=0b00      4KB granule for TTBR0 (Note: Different encoding to TG0)
                                            // A1=0          TTBR0 contains the ASID
                                            // AS=0          8-bit ASID
                                            // IPS=0         32-bit IPA space
    msr      tcr_el1, x0
    isb

    // Invalidate TLBs
    tlbi vmalle1
    dsb sy
    isb

    // Build single level translation table
    ldr x1, =_el1_l0_table

    // Zero all of table for unused entries
    mov x2, #512
zero_table:
    stp xzr, xzr, [x1], #16
    sub w2, w2, #2
    cbnz w2, zero_table

    ldr x1, =_el1_l0_table

    // [0]: 0x0000_0000–0x3FFF_FFFF (devices)
    ldr x0, =TT_S1_DEVICE_nGnRnE
    str x0, [x1]

    // [1]: 0x4000_0000–0x7FFF_FFFF (RAM)
    ldr x0, =TT_S1_NORMAL_WBWA
    orr x0, x0, #0x40000000
    str x0, [x1, #8]

    dsb sy
    isb

    // Enable MMU
    mrs x0, SCTLR_EL1
    orr x0, x0, #(1 << 0)  // M
    orr x0, x0, #(1 << 2)  // C
    orr x0, x0, #(1 << 12) // I
    msr SCTLR_EL1, x0
    isb

    // Enter into C
    ldr x30, =_stack_top
    mov SP, X30
    bl main
    b .

.section .data
