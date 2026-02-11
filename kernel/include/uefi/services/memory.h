#ifndef EFI_MEMORY_H
#define EFI_MEMORY_H

#include "uefi/types.h"

typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef enum {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef uint64_t EFI_PHYSICAL_ADDRESS;
typedef uint64_t EFI_VIRTUAL_ADDRESS;

typedef struct {
    uint32_t type;
    EFI_PHYSICAL_ADDRESS physical_start;
    EFI_VIRTUAL_ADDRESS virtual_start;
    uint64_t number_of_pages;
    uint64_t attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef EFI_STATUS (*EFI_ALLOCATE_PAGES) (
    EFI_ALLOCATE_TYPE type,
    EFI_MEMORY_TYPE memory_type,
    UINTN_T pages,
    EFI_PHYSICAL_ADDRESS *memory
);

typedef EFI_STATUS (*EFI_FREE_PAGES)(
    EFI_PHYSICAL_ADDRESS memory,
    UINTN_T pages
);

typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(
    UINTN_T *memory_map_size,
    EFI_MEMORY_DESCRIPTOR *memory_map,
    UINTN_T *map_key,
    UINTN_T *descriptor_size,
    uint32_t *descriptor_version
);

typedef EFI_STATUS (*EFI_ALLOCATE_POOL)(
    EFI_MEMORY_TYPE pool_type,
    UINTN_T size,
    void **buffer
);

typedef EFI_STATUS (*EFI_FREE_POOL)(
    void *buffer
);

#endif /* EFI_MEMORY_H */
