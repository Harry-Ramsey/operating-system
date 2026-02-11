#ifndef BOOT_SERVICES_H
#define BOOT_SERVICES_H

#include "uefi/types.h"
#include "uefi/services/memory.h"
#include <stdint.h>

typedef enum {
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef struct {
    EFI_HANDLE agent_handle;
    EFI_HANDLE controller_handle;
    uint32_t attributes;
    uint32_t open_count;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef struct _EFI_DEVICE_PATH_PROTOCOL {
    uint8_t Type;
    uint8_t SubType;
    uint8_t Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef void (*EFI_EVENT_NOTIFY)(
    EFI_EVENT event,
    void *context
);

typedef EFI_TPL (*EFI_RAISE_TPL)(
    EFI_TPL new_tpl
);

typedef void (*EFI_RESTORE_TPL)(
    EFI_TPL old_tpl
);

typedef EFI_STATUS (*EFI_CREATE_EVENT)(
    uint32_t type,
    EFI_TPL notify_tpl,
    EFI_EVENT_NOTIFY notify_function,
    const void *notify_context,
    EFI_EVENT *event
);

typedef EFI_STATUS (*EFI_SET_TIMER)(
    EFI_EVENT event,
    uint32_t type,
    uint64_t trigger_time
);

typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT)(
    UINTN_T number_of_events,
    EFI_EVENT *event,
    UINTN_T *index
);

typedef EFI_STATUS (*EFI_SIGNAL_EVENT)(
    EFI_EVENT event
);

typedef EFI_STATUS (*EFI_CLOSE_EVENT)(
    EFI_EVENT event
);

typedef EFI_STATUS (*EFI_CHECK_EVENT)(
    EFI_EVENT event
);

typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE *handle,
    EFI_GUID *protocol,
    EFI_INTERFACE_TYPE interface_type,
    void *interface
);

typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    void *old_interface,
    void *new_interface
);

typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    void *interface
);

typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL)(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    void **interface
);

typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY)(
    EFI_GUID *protocol,
    EFI_EVENT event,
    void **registration
);

typedef EFI_STATUS (*EFI_LOCATE_HANDLE)(
    EFI_LOCATE_SEARCH_TYPE search_type,
    EFI_GUID *protocol,
    void *search_key,
    UINTN_T *buffer_size,
    EFI_HANDLE *buffer
);

typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH)(
    EFI_GUID *protocol,
    EFI_DEVICE_PATH_PROTOCOL **device_path,
    EFI_HANDLE *device
);

typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE)(
    EFI_GUID *guid,
    void *table
);

typedef EFI_STATUS (*EFI_LOAD_IMAGE)(
    BOOLEAN boot_policy,
    EFI_HANDLE parent_image_handle,
    EFI_DEVICE_PATH_PROTOCOL *device_path,
    void *source_buffer,
    UINTN_T source_size,
    EFI_HANDLE *image_handle
);

typedef EFI_STATUS (*EFI_START_IMAGE)(
    EFI_HANDLE image_handle,
    UINTN_T *exit_data_size,
    CHAR16 **exit_data
);

typedef EFI_STATUS (*EFI_EXIT)(
    EFI_HANDLE image_handle,
    EFI_STATUS exit_status,
    UINTN_T exit_data_size,
    CHAR16 *exit_data
);

typedef EFI_STATUS (*EFI_UNLOAD_IMAGE)(
    EFI_HANDLE image_handle
);

typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(
    EFI_HANDLE image_handle,
    UINTN_T map_key
);

typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT)(
    uint64_t *count
);

typedef EFI_STATUS (*EFI_STALL)(
    UINTN_T microseconds
);

typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(
    UINTN_T timeout,
    uint64_t watchdog_code,
    UINTN_T data_size,
    CHAR16 *watchdog_data
);

typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER)(
    EFI_HANDLE controller_handle,
    EFI_HANDLE *driver_image_handle,
    EFI_DEVICE_PATH_PROTOCOL *remaining_device_path,
    BOOLEAN recursive
);

typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER)(
    EFI_HANDLE controller_handle,
    EFI_HANDLE driver_image_handle,
    EFI_HANDLE child_handle
);

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL)(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    void **interface,
    EFI_HANDLE agent_handle,
    EFI_HANDLE controller_handle,
    uint32_t attributes
);

typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    EFI_HANDLE agent_handle,
    EFI_HANDLE controller_handle
);

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION)(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **entry_buffer,
    UINTN_T *entry_count
);

typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE)(
    EFI_HANDLE handle,
    EFI_GUID ***protocol_buffer,
    UINTN_T *protocol_buffer_count
);

typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER)(
    EFI_LOCATE_SEARCH_TYPE search_type,
    EFI_GUID *protocol,
    void *search_key,
    UINTN_T *number_handles,
    EFI_HANDLE **buffer
);

typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(
    EFI_GUID *protocol,
    void *registration,
    void **interface
);

typedef EFI_STATUS (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    EFI_HANDLE *handle,
    ...
);

typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    EFI_HANDLE handle,
    ...
);

typedef EFI_STATUS (*EFI_CALCULATE_CRC32)(
    void *data,
    UINTN_T data_size,
    uint32_t *crc32
);

typedef void (*EFI_COPY_MEM)(
    void *destination,
    void *source,
    UINTN_T length
);

typedef void (*EFI_SET_MEM)(
    void *buffer,
    UINTN_T size,
    uint8_t value
);

typedef EFI_STATUS (*EFI_CREATE_EVENT_EX)(
    uint32_t type,
    EFI_TPL notify_tpl,
    EFI_EVENT_NOTIFY notify_function,
    const void *notify_context,
    const EFI_GUID *event_group,
    EFI_EVENT *event
);

EFI_TPL efi_raise_tpl(EFI_TPL new_tpl);

void efi_restore_tpl(EFI_TPL old_tpl);

EFI_STATUS efi_allocate_pages(
    EFI_ALLOCATE_TYPE type,
    EFI_MEMORY_TYPE memory_type,
    UINTN_T pages,
    EFI_PHYSICAL_ADDRESS *memory
);

EFI_STATUS efi_free_pages(EFI_PHYSICAL_ADDRESS memory, UINTN_T pages);

EFI_STATUS efi_get_memory_map(
    UINTN_T *memory_map_size,
    EFI_MEMORY_DESCRIPTOR *memory_map,
    UINTN_T *map_key,
    UINTN_T *descriptor_size,
    uint32_t *descriptor_version
);

EFI_STATUS efi_allocate_pool(EFI_MEMORY_TYPE pool_type, UINTN_T size, void
**buffer);

EFI_STATUS efi_free_pool(void *buffer);

EFI_STATUS efi_create_event(
    uint32_t type,
    EFI_TPL notify_tpl,
    EFI_EVENT_NOTIFY notify_function,
    const void *notify_context,
    EFI_EVENT *event
);

EFI_STATUS efi_set_timer(EFI_EVENT event, uint32_t type, uint64_t trigger_time);

EFI_STATUS efi_wait_for_event(UINTN_T number_of_events, EFI_EVENT *event, UINTN_T *index);

EFI_STATUS efi_signal_event(EFI_EVENT event);

EFI_STATUS efi_close_event(EFI_EVENT event);

EFI_STATUS efi_check_event(EFI_EVENT event);

EFI_STATUS efi_install_protocol_interface(
    EFI_HANDLE *handle,
    EFI_GUID *protocol,
    EFI_INTERFACE_TYPE interface_type,
    void *interface
);

EFI_STATUS efi_reinstall_protocol_interface(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    void *old_interface,
    void *new_interface
);

EFI_STATUS efi_uninstall_protocol_interface(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    void *interface
);

EFI_STATUS efi_handle_protocol(EFI_HANDLE handle, EFI_GUID *protocol, void **interface);

EFI_STATUS efi_register_protocol_notify(EFI_GUID *protocol, EFI_EVENT event, void **registration);

EFI_STATUS efi_locate_handle(
    EFI_LOCATE_SEARCH_TYPE search_type,
    EFI_GUID *protocol,
    void *search_key,
    UINTN_T *buffer_size,
    EFI_HANDLE *buffer
);

EFI_STATUS efi_locate_device_path(
    EFI_GUID *protocol,
    EFI_DEVICE_PATH_PROTOCOL **device_path,
    EFI_HANDLE *device
);

EFI_STATUS efi_install_configuration_table(EFI_GUID *guid, void *table);

EFI_STATUS efi_load_image(
    BOOLEAN boot_policy,
    EFI_HANDLE parent_image_handle,
    EFI_DEVICE_PATH_PROTOCOL *device_path,
    void *source_buffer,
    UINTN_T source_size,
    EFI_HANDLE *image_handle
);

EFI_STATUS efi_start_image(EFI_HANDLE image_handle, UINTN_T *exit_data_size, CHAR16 **exit_data);

EFI_STATUS efi_exit(
    EFI_HANDLE image_handle,
    EFI_STATUS exit_status,
    UINTN_T exit_data_size,
    CHAR16 *exit_data
);

EFI_STATUS efi_unload_image(EFI_HANDLE image_handle);

EFI_STATUS efi_exit_boot_services(EFI_HANDLE image_handle, UINTN_T map_key);

EFI_STATUS efi_get_next_monotonic_count(uint64_t *count);

EFI_STATUS efi_stall(UINTN_T microseconds);

EFI_STATUS efi_set_watchdog_timer(
    UINTN_T timeout,
    uint64_t watchdog_code,
    UINTN_T data_size,
    CHAR16 *watchdog_data
);

EFI_STATUS efi_connect_controller(
    EFI_HANDLE controller_handle,
    EFI_HANDLE *driver_image_handle,
    EFI_DEVICE_PATH_PROTOCOL *remaining_device_path,
    BOOLEAN recursive
);

EFI_STATUS efi_disconnect_controller(
    EFI_HANDLE controller_handle,
    EFI_HANDLE driver_image_handle,
    EFI_HANDLE child_handle
);

EFI_STATUS efi_open_protocol(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    void **interface,
    EFI_HANDLE agent_handle,
    EFI_HANDLE controller_handle,
    uint32_t attributes
);

EFI_STATUS efi_close_protocol(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    EFI_HANDLE agent_handle,
    EFI_HANDLE controller_handle
);

EFI_STATUS efi_open_protocol_information(
    EFI_HANDLE handle,
    EFI_GUID *protocol,
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **entry_buffer,
    UINTN_T *entry_count
);

EFI_STATUS efi_protocols_per_handle(
    EFI_HANDLE handle,
    EFI_GUID ***protocol_buffer,
    UINTN_T *protocol_buffer_count
);

EFI_STATUS efi_locate_handle_buffer(
    EFI_LOCATE_SEARCH_TYPE search_type,
    EFI_GUID *protocol,
    void *search_key,
    UINTN_T *number_handles,
    EFI_HANDLE **buffer
);

EFI_STATUS efi_locate_protocol(EFI_GUID *protocol, void *registration, void **interface);

EFI_STATUS efi_install_multiple_protocol_interfaces(EFI_HANDLE *handle, ...);

EFI_STATUS efi_uninstall_multiple_protocol_interfaces(EFI_HANDLE handle, ...);

EFI_STATUS efi_calculate_crc32(void *data, UINTN_T data_size, uint32_t *crc32);

void efi_copy_mem(void *destination, void *source, UINTN_T length);

void efi_set_mem(void *buffer, UINTN_T size, uint8_t value);

EFI_STATUS efi_create_event_ex(
    uint32_t type,
    EFI_TPL notify_tpl,
    EFI_EVENT_NOTIFY notify_function,
    const void *notify_context,
    const EFI_GUID *event_group,
    EFI_EVENT *event
);

#endif /* BOOT_SERVICES_H */
