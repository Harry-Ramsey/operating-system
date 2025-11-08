#include "mm/device_tree.h"
#include <stdint.h>

#define NULL 0x00

static inline uint32_t to_little_endian(uint32_t value) {
    return ((value >> 24) & 0xff) |
           ((value << 8) & 0xff0000) |
           ((value >> 8) & 0xff00) |
           ((value << 24) & 0xff000000);
}

/**
 * @brief Aligns a pointer to the next 4-byte boundary.
 */
static inline const void *fdt_align_ptr(const void *ptr) {
    uintptr_t p = (uintptr_t)ptr;
    // Add 3 and then mask off the lower 2 bits to round up.
    return (const void *)((p + 3) & ~3);
}

/**
 * @brief Correct standard strlen implementation.
 */
static uint32_t fdt_strlen(const char *str) {
    const char *s = str;
    while (*s) {
        s++;
    }
    return (s - str);
}

/**
 * @brief Correct standard strcmp implementation.
 * @return 0 if s1 and s2 are equal.
 * < 0 if s1 < s2.
 * > 0 if s1 > s2.
 */
static int fdt_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    // Return the difference of the first non-matching characters
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

const uint32_t *fdt_find_structure(const struct fdt_header *fdt, const char *name) {
    // Get a pointer to the start of the structure block
    const char *fdt_base = (const char *)fdt;
    const uint32_t *structure_block = (const uint32_t *)(fdt_base + to_little_endian(fdt->off_dt_struct));
    const uint32_t *end_block = (const uint32_t *)(fdt_base + to_little_endian(fdt->off_dt_struct) + to_little_endian(fdt->size_dt_struct));

    // Iterate through the structure block until FDT_END or out of bounds
    while (structure_block < end_block) {
        uint32_t token = to_little_endian(*structure_block);
        switch (token) {
            case FDT_BEGIN_NODE:
                // The node name immediately follows the token.
                const char *node_name = (const char *)(structure_block + 1);
                if (fdt_strcmp(node_name, name) == 0) {
                    return structure_block;
                }

                const char *next_token = node_name + fdt_strlen(node_name) + 1;
                const void *aligned_token = fdt_align_ptr(next_token);
                structure_block = (const uint32_t *)(aligned_token - 1);
                break;
            case FDT_PROP:
                uint32_t len_bytes = to_little_endian(*(structure_block + 1));
                const char *prop_data = (const char *)(structure_block + 3);

                const char *prop_data_end = prop_data + len_bytes;
                const void *aligned_next = fdt_align_ptr(prop_data_end);
                structure_block = (const uint32_t *)aligned_next - 1;
                break;
            case FDT_END_NODE:
            case FDT_NOP:
                break;
            case FDT_END:
                // End of structure block.
                return NULL;
            default:
                // Unknown or corrupted token. Device tree cannot be passed
                return NULL;
        }
        // Advance to the next 32-bit word
        structure_block++;
    }
    // Reached end of block without finding FDT_END (or the node)
    return NULL;
}

const uint32_t *fdt_find_property(const struct fdt_header *fdt, const uint32_t *structure, const char *property) {
    if (!structure)
        return NULL;

    const char *fdt_strings = fdt + to_little_endian(fdt->off_dt_strings);

    const uint32_t *token = structure;
    while (*token != FDT_END_NODE) {
        switch (*token) {
            case FDT_PROP:
                uint32_t len = to_little_endian(token[1]);
                uint32_t nameoff = to_little_endian(token[2]);
                const char *name = fdt_strings + nameoff;
                if (fdt_strcmp(property, name))
                    return token;
                break;
            case FDT_NOP:
                break;
            case FDT_BEGIN_NODE:
            case FDT_END_NODE:
            case FDT_END:
                return NULL;
            default:
                return NULL;
        }


    }


    return NULL;
}

void fdt_get_ram_info(const struct fdt_header *fdt) {
    const uint32_t *memory_block = fdt_find_structure(fdt, "memory");

}

