#include "mm/mmu.h"
#include "mm/device_tree.h"
#include <stdint.h>

#define PAGE_SHIFT 12

void mmu_invalidate_caches() {
    asm(
        ""
    );
}

void mmu_init(const fdt) {
    // Allocate pages for the relevant tables

}

void mmu_map_va_to_phys(uint64_t va, uint64_t phys, uint64_t size, uint64_t perms) {
    pte_t desc;
    if (size == 0)
        return;

    uint64_t l0_index = (va >> 39) & 0x1FF;
    pte_t l0_entry = ;
    uint64_t l1_index = (va >> 30) & 0x1FF;
    pte_t l1_entry = ;
    desc = el1_l1_table[l1_index];
#if defined(GRANULE_16KB) || defined(GRANULE_4KB)
    uint64_t l2_index = (va >> 21) & 0x1FF;
    pte_t l2_entry = ;
    desc = el1_l2_table[l2_index];
#endif
#ifdef GRANULE_4KB
    uint64_t l3_index = (va >> 12) & 0x1FF;
    pte_t l3_entry = ;
    desc = el1_l3_table[l3_index];
#endif

    // Setup a new page, previous levels must share permissions

    /*
     * Set up execute permissions for the page.
     * kernel-space pages are not executable to user-space and vice versa.
     */
    if (perms & MMU_PROT_EXEC) {
        if (perms & MMU_PROT_UNPRIVILEGED)
            desc |= PXN_FLAG;
        else
            desc |= UXN_FLAG;
    } else {
        desc |= (PXN_FLAG|UXN_FLAG);
    }

    // AP[2:1] set bit 2 to 0
    if (!(perms & MMU_PROT_WRITE)) {
        if (perms & MMU_PROT_UNPRIVILEGED)
            desc |= UNPRIVILEGED_FLAG;
        desc |= READ_ONLY_FLAG;
    } else {
        /* A page cannot be writeable and executable. */
        desc |= (PXN_FLAG | UXN_FLAG);
    }
}

void mmu_unmap_va_to_phys(uint64_t va, uint64_t phys, uint64_t size) {
    pte_t desc;
    uint64_t pages = (size >> PAGE_SHIFT);

    for (uint64_t pages = (size >> PAGE_SHIFT); pages > 0; pages--) {
        uint64_t l0_index = (va >> 39) & 0x1FF;
        uint64_t l1_index = (va >> 30) & 0x1FF;

#if defined(GRANULE_16KB) || defined(GRANULE_4KB)
        uint64_t l1_index = (va >> 21) & 0x1FF;
#endif
#ifdef GRANULE_4KB
        uint64_t l1_index = (va >> 12) & 0x1FF;
#endif



    }

    // Remove all entire entry
    desc = 0x0;
}
