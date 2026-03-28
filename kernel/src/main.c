#include <stddef.h>
#include <stdint.h>

#include "uefi/protocols/simple_text_output.h"
#include "uefi/services/memory.h"
#include "uefi/system.h"
#include "console/uart.h"
#include "uefi/types.h"

EFI_STATUS EfiMain(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table) {
    EFI_STATUS status;
    UINTN_T memory_map_size = 0;
    EFI_MEMORY_DESCRIPTOR * memory_map = NULL;
    UINTN_T map_key = 0;
    UINTN_T descriptor_size;
    uint32_t descriptor_version = 0;
    EFI_BOOT_SERVICES *boot_services = system_table->BootServices;
    status = boot_services->get_memory_map(&memory_map_size, memory_map,
                                           &map_key, &descriptor_size, &descriptor_version);

    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *output = system_table->console_out;
    output->clearscreen(output);
    output->ouputstring(output, L"Hello World\r\n");

    return 0;
}