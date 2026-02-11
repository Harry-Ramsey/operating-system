#ifndef SIMPLE_TEXT_INPUT_H
#define SIMPLE_TEXT_INPUT_H

#include "uefi/types.h"

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID                                    \
  {0x387477c1, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_INPUT_RESET) (
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *protocol,
    BOOLEAN extended_verification
);

typedef struct EFI_INPUT_KEY {
    uint16_t scan_code;
    CHAR16 unicode_char;
} EFI_INPUT_KEY;

typedef EFI_STATUS (*EFI_INPUT_READ_KEY) (
    struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *protocol,
    EFI_INPUT_KEY *key
);

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_INPUT_RESET reset;
    EFI_INPUT_READ_KEY read_key_stroke;
    EFI_EVENT wait_for_key;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

#endif /* SIMPLE_TEXT_INPUT_H */
