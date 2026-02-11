#ifndef UEFI_SYSTEM_H
#define UEFI_SYSTEM_H

#include "uefi/types.h"
#include "uefi/protocols/simple_text_input.h"
#include "uefi/protocols/simple_text_output.h"
#include "uefi/services/boot.h"
#include "uefi/services/runtime.h"

// TODO: Review code

typedef struct EFI_TABLE_HEADER {
    uint64_t signature;
    uint32_t revision;
    uint32_t header_size;
    uint32_t crc32;
    uint32_t reserved;
} EFI_TABLE_HEADER;

typedef struct EFI_CONFIGURATION_TABLE {
    EFI_GUID vendor_guid;
    void *vendor_table;
} EFI_CONFIGURATION_TABLE;

typedef struct EFI_RUNTIME_SERVICES {
    EFI_TABLE_HEADER header;

    EFI_GET_TIME get_time;
    EFI_SET_TIME set_time;
    EFI_GET_WAKEUP_TIME get_wakeup_time;
    EFI_SET_WAKEUP_TIME set_wakeup_time;

    EFI_SET_VIRTUAL_ADDRESS_MAP set_virtual_address_map;
    EFI_CONVERT_POINTER convert_pointer;

    EFI_GET_VARIABLE get_variable;
    EFI_GET_NEXT_VARIABLE_NAME get_next_variable_name;
    EFI_SET_VARIABLE set_variable;

    EFI_GET_NEXT_HIGH_MONO_COUNT get_next_high_monotonic_count;
    EFI_RESET_SYTEM reset_system;

    EFI_UPDATE_CAPSURE update_capsule;
    EFI_QUERY_CAPSULE_CAPABILITIES query_capsule_capabilities;

    EFI_QUERY_VARIABLE_INFO query_variable_info;
} EFI_RUNTIME_SERVICES;

typedef struct EFI_BOOT_SERVICES {
    EFI_TABLE_HEADER header;

    EFI_RAISE_TPL raise_tpl;
    EFI_RESTORE_TPL restore_tpl;

    EFI_ALLOCATE_PAGES allocate_pages;
    EFI_FREE_PAGES free_pages;
    EFI_GET_MEMORY_MAP get_memory_map;
    EFI_ALLOCATE_POOL allocate_pool;
    EFI_FREE_POOL free_pool;

    EFI_CREATE_EVENT create_event;
    EFI_SET_TIMER set_timer;
    EFI_WAIT_FOR_EVENT wait_for_event;
    EFI_SIGNAL_EVENT signal_event;
    EFI_CLOSE_EVENT close_event;
    EFI_CHECK_EVENT check_event;

    EFI_INSTALL_PROTOCOL_INTERFACE install_protocol_interface;
    EFI_REINSTALL_PROTOCOL_INTERFACE reinstall_protocol_interface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE uninstall_protocol_interface;
    EFI_HANDLE_PROTOCOL handle_protocol;
    void *reserved;
    EFI_REGISTER_PROTOCOL_NOTIFY register_protocol_notify;
    EFI_LOCATE_HANDLE locate_handle;
    EFI_LOCATE_DEVICE_PATH locate_device_path;
    EFI_INSTALL_CONFIGURATION_TABLE install_configuration_table;

    EFI_LOAD_IMAGE load_image;
    EFI_START_IMAGE start_image;
    EFI_EXIT exit;
    EFI_UNLOAD_IMAGE unload_image;
    EFI_EXIT_BOOT_SERVICES exit_boot_services;

    EFI_GET_NEXT_MONOTONIC_COUNT get_next_monotonic_count;
    EFI_STALL stall;
    EFI_SET_WATCHDOG_TIMER set_watchdog_timer;

    EFI_CONNECT_CONTROLLER connect_controller;
    EFI_DISCONNECT_CONTROLLER disconnect_controller;

    EFI_OPEN_PROTOCOL open_protocol;
    EFI_CLOSE_PROTOCOL close_protocol;
    EFI_OPEN_PROTOCOL_INFORMATION open_protocol_information;

    EFI_PROTOCOLS_PER_HANDLE protocols_per_handle;
    EFI_LOCATE_HANDLE_BUFFER locate_handle_buffer;
    EFI_LOCATE_PROTOCOL locate_protocol;
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES install_multiple_protocol_interfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES uninstall_multiple_protocol_interfaces;

    EFI_CALCULATE_CRC32 calculate_crc32;

    EFI_COPY_MEM copy_mem;
    EFI_SET_MEM set_mem;
    EFI_CREATE_EVENT_EX create_event_ex;
} EFI_BOOT_SERVICES;

typedef struct EFI_SYSTEM_TABLE {
    EFI_TABLE_HEADER header;
    CHAR16 *firmware_vendor;
    uint32_t firmware_revision;
    EFI_HANDLE console_in_handle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL *console_in;
    EFI_HANDLE console_out_handle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *console_out;
    EFI_HANDLE StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StdErr;
    EFI_RUNTIME_SERVICES *RuntimeServices;
    EFI_BOOT_SERVICES *BootServices;
    UINTN_T NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE *ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif /* UEFI_SYSTEM_H */
