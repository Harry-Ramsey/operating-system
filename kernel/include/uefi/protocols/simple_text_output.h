#ifndef SIMPLE_TEXT_OUTPUT_H
#define SIMPLE_TEXT_OUTPUT_H

#include "uefi/types.h"

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID                                   \
  {0x387477c2, 0x69c7, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_TEXT_RESET)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    uint8_t extended_verification
);

typedef EFI_STATUS (*EFI_TEXT_STRING)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    CHAR16 *string
);

typedef EFI_STATUS (*EFI_TEXT_TEST_STRING)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    CHAR16 *string
);

typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    UINTN_T mode,
    UINTN_T *columns,
    UINTN_T *rows
);

typedef EFI_STATUS (*EFI_TEXT_SET_MODE)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    uint64_t mode
);

typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    UINTN_T attribute
);

typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol
);

typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    uint64_t column,
    uint64_t row
);

typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR)(
    struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *protocol,
    BOOLEAN visible
);

typedef struct SIMPLE_TEXT_OUTPUT_MODE {
    int32_t maxmode;
    int32_t mode;
    int32_t attribute;
    int32_t cursorcolumn;
    int32_t cusorrow;
    BOOLEAN cursorvisible;
} SIMPLE_TEXT_OUTPUT_MODE;

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET reset;
    EFI_TEXT_STRING ouputstring;
    EFI_TEXT_TEST_STRING teststring;
    EFI_TEXT_QUERY_MODE querymode;
    EFI_TEXT_SET_MODE setmode;
    EFI_TEXT_SET_ATTRIBUTE setattribute;
    EFI_TEXT_CLEAR_SCREEN clearscreen;
    EFI_TEXT_SET_CURSOR_POSITION setcursorposition;
    EFI_TEXT_ENABLE_CURSOR enablecursor;
    SIMPLE_TEXT_OUTPUT_MODE *mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#endif /* SIMPLE_TEXT_OUTPUT_H */
