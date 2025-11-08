#ifndef MMU_H
#define MMU_H

#include <stdint.h>
#include "device_tree.h"

#define NS_FLAG                  (1ULL << 63)
#define UXN_FLAG                 (1ULL << 60)
#define PXN_FLAG                 (1ULL << 59)
#define PERMISSION_FLAG          (3ULL << 61)
#define READ_ONLY_FLAG           (1ULL << 62)
#define UNPRIVILEGED_FLAG        (1ULL << 61)

#define TABLE_DESCRIPTOR_FLAG    (1ULL << 1)
#define VALID_DESCRIPTOR_FLAG    (1ULL)

// Define permissions
#define MMU_PROT_NONE            0x00
#define MMU_PROT_READ            0x01
#define MMU_PROT_WRITE           0x02
#define MMU_PROT_EXEC            0x04
#define MMU_PROT_UNPRIVILEGED    0x08

typedef uint64_t pte_t;

/*
 * Define pointers to our page tables here, these need to be setup at runtime
 * since the device tree contains the size of RAM.
 */
pte_t *el1_l0_table;
pte_t *el1_l1_table;
#if defined(GRANULE_16KB) || defined(GRANULE_4KB)
pte_t *el1_l2_table;
#endif
#ifdef GRANULE_4KB
pte_t *el1_l3_table;
#endif

void mmu_init();
void mmu_map_va_to_phys(uint64_t va, uint64_t phys, uint64_t size, uint64_t perms);
void mmu_unmap_va_to_phys(uint64_t va, uint64_t phys, uint64_t size);

#endif /* MMU_H */
