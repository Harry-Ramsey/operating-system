#ifndef SYSREG_H
#define SYSREG_H

#include <stdint.h>

#include "stringify.h"

#define READ_SYSREG(reg) ({                                               \
    uint64_t _v;                                                          \
    __asm__ volatile("mrs %0, " __stringify(reg) : "=r"(_v));             \
    _v;                                                                   \
})

#define WRITE_SYSREG(reg, value) do {                                     \
    __asm__ volatile("msr " __stringify(reg) ", %0" :: "r"(value));       \
} while (0)

#define TCR_EL1     S3_0_C2_C0_2
#define MAIR_EL1    S3_0_C10_C2_0
#define SCTLR_EL1   S3_0_C1_C0_0

#define SCTLR_EL1_I     (1ULL << 12)
#define SCTLR_EL1_SA0   (1ULL << 4)
#define SCTLR_EL1_SA    (1ULL << 3)
#define SCTLR_EL1_C     (1ULL << 2)
#define SCTLR_EL1_A     (1ULL << 1)
#define SCTLR_EL1_M     (1ULL << 0)

#define MAIR_EL1_DEVICE (0x00ULL)
#define MAIR_EL1_NORMAL (0xffULL)

#endif /* SYSREG_H */