#ifndef UEFI_TYPES_H
#define UEFI_TYPES_H

#include <stdint.h>

typedef uint64_t UINTN_T;

typedef uint8_t   BOOLEAN;
typedef uint16_t  CHAR16;

typedef struct {
    uint32_t data1;
    uint16_t data2;
    uint16_t data3;
    uint8_t data4[8];
} EFI_GUID __attribute__((aligned(8)));

typedef uint64_t EFI_STATUS;
typedef void* EFI_HANDLE;
typedef void* EFI_EVENT;
typedef uint64_t EFI_LBA;
typedef uint64_t EFI_TPL;

typedef struct {
    uint8_t addr[32];
} EFI_MAC_ADDRESS;

typedef struct {
    uint8_t addr[4];
} EFI_IPv4_ADDRESS;

typedef struct {
    uint8_t addr[16];
} EFI_IPv6_ADDRESS;

typedef union {
    uint32_t addr[4];
    EFI_IPv4_ADDRESS v4;
    EFI_IPv6_ADDRESS v6;
} EFI_IP_ADDRESS __attribute__((aligned(4)));

#endif /* UEFI_TYPES_H */
