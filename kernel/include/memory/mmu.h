#ifndef MMU_H
#define MMU_H

#define PTE_NS      (0b1  << 63)
#define PTE_AP      (0b11 << 61)
#define PTE_PXN     (0b1 << 54)
#define PTE_UXN     (0b1 << 53)
#define PTE_CGB     (0b1 << 52)
#define PTE_DBM     (0b1 << 51)

#define PTE_TABLE   (0b1  <<  1)
#define PTE_VALID   (0b1  <<  0)

#define PTE_NG      (0b1  << 11)
#define PTE_AF      (0b1  << 10)
#define PTE_SH      (0b11 <<  8)
#define PTE_AP      (0b11 <<  6)
#define PTE_NS      (0b1  <<  5)
#define PTE_AI      (0b111 << 2)

#define MMU_SH_NONE     (0b00)
#define MMU_SH_RES      (0b01)
#define MMU_SH_OUTER    (0b10)
#define MMU_SH_INNER    (0b11)


#define SCTLR_EL1_SA0   (0b1 << 4)
#define SCTLR_EL1_SA    (0b1 << 3)
#define SCTLR_EL1_C     (0b1 << 2)
#define SCTLR_EL1_A     (0b1 << 1)
#define SCTLR_EL1_M     (0b1 << 0)

void mmu_enable();
void mmu_disable();

#endif /* MMU_H */