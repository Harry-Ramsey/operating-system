#ifndef RUNTIME_SERVICES_H
#define RUNTIME_SERVICES_H

#include "uefi/types.h"
#include "uefi/services/memory.h"

#define EFI_SUCCESS ((EFI_STATUS)0)
#define EFI_INVALID_PARAMETER ((EFI_STATUS)2)
#define EFI_UNSUPPORTED ((EFI_STATUS)3)

#define EFI_UNSPECIFIED_TIMEZONE ((int16_t)0x07FF)
#define EFI_TIME_ADJUST_DAYLIGHT ((uint8_t)0x01)
#define EFI_TIME_IN_DAYLIGHT ((uint8_t)0x02)

typedef enum {
    EfiResetCold,
    EfiResetWarm,
    EfiResetShutdown,
    EfiResetPlatformSpecific,
} EFI_RESET_TYPE;

typedef struct EFI_CAPSULE_HEADER EFI_CAPSULE_HEADER;

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t pad1;
    uint32_t nanosecond;
    int16_t timezone;
    uint8_t daylight;
    uint8_t pad2;
} EFI_TIME;

typedef struct {
    uint32_t resolution;
    uint32_t accuracy;
    BOOLEAN sets_to_zero;
} EFI_TIME_CAPABILITIES;

typedef EFI_STATUS (*EFI_GET_TIME)(
    EFI_TIME *time,
    EFI_TIME_CAPABILITIES *capabilities
);

typedef EFI_STATUS (*EFI_SET_TIME)(
    EFI_TIME *time
);

typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME)(
    BOOLEAN *enabled,
    BOOLEAN *pending,
    EFI_TIME *time
);

typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME)(
    BOOLEAN enable,
    EFI_TIME *time
);

typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(
    UINTN_T memory_map_size,
    UINTN_T descriptor_size,
    uint32_t descriptor_version,
    EFI_MEMORY_DESCRIPTOR *virtual_map
);

typedef EFI_STATUS (*EFI_CONVERT_POINTER)(
    UINTN_T debug_disposition,
    void **address
);

typedef EFI_STATUS (*EFI_GET_VARIABLE)(
    CHAR16 *variable_name,
    EFI_GUID *vendor_guid,
    uint32_t *attributes,
    UINTN_T *data_size,
    void *data
);

typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(
    UINTN_T *variable_name_size,
    CHAR16 *variable_name,
    EFI_GUID *vendor_guid
);

typedef EFI_STATUS (*EFI_SET_VARIABLE)(
    CHAR16 *variable_name,
    EFI_GUID *vendor_guid,
    uint32_t attributes,
    UINTN_T data_size,
    void *data
);

typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONO_COUNT)(
    uint32_t *high_count
);

typedef void (*EFI_RESET_SYTEM)(
    EFI_RESET_TYPE reset_type,
    EFI_STATUS reset_status,
    UINTN_T data_size,
    CHAR16 *reset_data
);

typedef EFI_STATUS (*EFI_UPDATE_CAPSURE)(
    EFI_CAPSULE_HEADER **capsule_header_array,
    UINTN_T capsule_count,
    EFI_PHYSICAL_ADDRESS scatter_gather_list
);

typedef EFI_STATUS (*EFI_QUERY_CAPSULE_CAPABILITIES)(
    EFI_CAPSULE_HEADER **capsule_header_array,
    UINTN_T capsule_count,
    UINTN_T *maximum_capsule_size,
    EFI_RESET_TYPE *reset_type
);

typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(
    uint32_t attributes,
    uint64_t *maximum_variable_storage_size,
    uint64_t *remaining_variable_storage_size,
    uint64_t *maximum_variable_size
);

EFI_STATUS efi_get_time(EFI_TIME *time, EFI_TIME_CAPABILITIES *capabilities);

EFI_STATUS efi_set_time(EFI_TIME *time);

EFI_STATUS efi_get_wakeup_time(BOOLEAN *enabled, BOOLEAN *pending, EFI_TIME *time);

EFI_STATUS efi_set_wakeup_time(BOOLEAN enable, EFI_TIME *time);

EFI_STATUS efi_set_virtual_address_map(
    UINTN_T memory_map_size,
    UINTN_T descriptor_size,
    uint32_t descriptor_version,
    EFI_MEMORY_DESCRIPTOR *virtual_map
);

EFI_STATUS efi_convert_pointer(UINTN_T debug_disposition, void **address);
EFI_STATUS efi_get_variable(
    CHAR16 *variable_name,
    EFI_GUID *vendor_guid,
    uint32_t *attributes,
    UINTN_T *data_size,
    void *data
);

EFI_STATUS efi_get_next_variable_name(
    UINTN_T *variable_name_size,
    CHAR16 *variable_name,
    EFI_GUID *vendor_guid
);

EFI_STATUS efi_set_variable(
    CHAR16 *variable_name,
    EFI_GUID *vendor_guid,
    uint32_t attributes,
    UINTN_T data_size,
    void *data
);

EFI_STATUS efi_get_next_high_monotonic_count(uint32_t *high_count);
void efi_reset_system(
    EFI_RESET_TYPE reset_type,
    EFI_STATUS reset_status,
    UINTN_T data_size,
    CHAR16 *reset_data
);

EFI_STATUS efi_update_capsule(
    EFI_CAPSULE_HEADER **capsule_header_array,
    UINTN_T capsule_count,
    EFI_PHYSICAL_ADDRESS scatter_gather_list
);

EFI_STATUS efi_query_capsule_capabilities(
    EFI_CAPSULE_HEADER **capsule_header_array,
    UINTN_T capsule_count,
    UINTN_T *maximum_capsule_size,
    EFI_RESET_TYPE *reset_type
);

EFI_STATUS efi_query_variable_info(
    uint32_t attributes,
    uint64_t *maximum_variable_storage_size,
    uint64_t *remaining_variable_storage_size,
    uint64_t *maximum_variable_size
);

#endif /* RUNTIME_SERVICES_H */
