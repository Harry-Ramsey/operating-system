#include "memory/mmu.h"
#include "sysreg.h"

#include <stddef.h>
#include <stdint.h>

void mmu_enable() {
    uint64_t mair_el1 = 0;
    uint64_t tcr_el1 = 0;
    uint64_t sctlr_el1 = 0;

    // Attr[0] - Device Memory
    // Attr[1] - Normal Memory
    mair_el1 = (MAIR_EL1_DEVICE << 0) | (MAIR_EL1_NORMAL << 8);

    tcr_el1 =
        // TTBR0
        (16ULL << 0) |    // T0SZ = 16 -> 48-bit VA
        (0b01ULL << 8) |  // IRGN0 = Write-Back, Write-Allocate
        (0b01ULL << 10) | // ORGN0 = Write-Back, Write-Allocate
        (0b11ULL << 12) | // SH0 = inner shareable
        (0b00ULL << 14) | // TG0 = 4KB granule
        // TTBR1
        (16ULL << 16) |   // T1SZ = 16 -> 48-bit VA
        (0b01ULL << 24) | // IRGN1 = Write-Back, Write-Allocate
        (0b01ULL << 26) | // ORGN1 = Write-Back, Write-Allocate
        (0b11ULL << 28) | // SH1 = inner shareable
        (0b10ULL << 30) | // TG1 = 4KB granule
                          // TG1 and TG0 have different encodings
                          // TG1[31:30] - bit[31]=RES1, bit[30]=0
        // Common
        (0b010ULL << 32); // IPS = 40-bit PA (1TB) (needed for >4GB RAM)

    WRITE_SYSREG(MAIR_EL1, mair_el1);
    WRITE_SYSREG(TCR_EL1, tcr_el1);
    __asm__ volatile("isb");

    sctlr_el1 = READ_SYSREG(SCTLR_EL1);
    sctlr_el1 |= SCTLR_EL1_M | SCTLR_EL1_C | SCTLR_EL1_I;
    WRITE_SYSREG(SCTLR_EL1, sctlr_el1);
    __asm__ volatile("isb");

}

uint64_t *mmu_walk_page_tables(uint64_t *l0_table, uint64_t va) {
    uint64_t *l1_table;
    uint64_t *l2_table;
    uint64_t *l3_table;

    uint64_t l0_index = L0_INDEX(va);
    uint64_t l1_index = L1_INDEX(va);
    uint64_t l2_index = L2_INDEX(va);
    uint64_t l3_index = L3_INDEX(va);

    if (!(l0_table[l0_index] | PTE_VALID)) {
        l1_table = mmu_alloc_page_table();
        if (!l1_table)
            return NULL;

        l0_table[l0_index] = (uint64_t) l1_table | PTE_VALID | PTE_TABLE;
    }
    l1_table = (uint64_t *)(l0_table[l0_index] & PTE_ADDR_MASK);

    if (!(l1_table[l1_index] | PTE_VALID)) {
        l2_table = mmu_alloc_page_table();
        if (!l2_table)
            return NULL;

        l1_table[l1_index] = (uint64_t) l2_table | PTE_VALID | PTE_TABLE;
    }
    l2_table = (uint64_t *)(l1_table[l1_index] & PTE_ADDR_MASK);

    if (!(l2_table[l2_index] | PTE_VALID)) {
        l3_table = mmu_alloc_page_table();
        if (!l3_table)
            return NULL;

        l2_table[l2_index] = (uint64_t) l3_table | PTE_VALID | PTE_TABLE;
    }
    l3_table = (uint64_t *)(l2_table[l2_index] & PTE_ADDR_MASK);

    return &l3_table[l3_index];
}

uint64_t *mmu_map_virt_to_phys(uint64_t *l0_table, uint64_t virt, uint64_t phys, uint64_t flags) {
    uint64_t *l1_table;
    uint64_t *l2_table;
    uint64_t *l3_table;

    uint64_t l0_index = L0_INDEX(virt);
    uint64_t l1_index = L1_INDEX(virt);
    uint64_t l2_index = L2_INDEX(virt);
    uint64_t l3_index = L3_INDEX(virt);

    if (!(l0_table[l0_index] | PTE_VALID)) {
        if (!(l1_table = mmu_alloc_page_table()))
            return NULL;

        l0_table[l0_index] = (uint64_t)l1_table | PTE_VALID | PTE_TABLE;
    }
    l1_table = (uint64_t *)(l0_table[l0_index] & PTE_ADDR_MASK);

    if (!(l1_table[l1_index] | PTE_VALID)) {
        if (!(l2_table = mmu_alloc_page_table()))
            return NULL;

        l1_table[l1_index] = (uint64_t)l2_table | PTE_VALID | PTE_TABLE;
    }
    l2_table = (uint64_t *)(l1_table[l1_index] & PTE_ADDR_MASK);

    if (!(l2_table[l2_index] | PTE_VALID)) {
        if (!(l3_table = mmu_alloc_page_table()))
            return NULL;

        l2_table[l2_index] = (uint64_t)l3_table | PTE_VALID;
    }
    l3_table = (uint64_t *)(l2_table[l2_index] & PTE_ADDR_MASK);

    return &l3_table[l3_index];
}

void mmu_disable() {

}
