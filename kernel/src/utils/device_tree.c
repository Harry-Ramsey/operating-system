#include "mm/device_tree.h"
#include <stdint.h>
#include <stddef.h>

// TODO:
// 1) Cleanup this file
// 1a) Move defines and to_little_endian to header

static inline uint32_t to_little_endian(uint32_t value) {
    return ((value >> 24) & 0xff) |
           ((value << 8) & 0xff0000) |
           ((value >> 8) & 0xff00) |
           ((value << 24) & 0xff000000);
}

#define ALIGN(x, a)   (((x) + ((a) - 1)) & ~((a) - 1))
#define FDT_ALIGN(x) ALIGN(x, 4)
#define FDT_ALIGN_PTR(p) ((const void *)ALIGN((uintptr_t)(p), 4))

static int fdt_node_name_eq(const char *fdt_name, const char *target_name) {
    int len = strlen(target_name);
    if (strncmp(fdt_name, target_name, len) == 0) {
        // Match if the FDT name ends here, or continues with '@'
        if (fdt_name[len] == '\0' || fdt_name[len] == '@') {
            return 1;
        }
    }
    return 0;
}

const uint32_t *fdt_skip_property(const uint32_t *property) {
    if (to_little_endian(property[0]) != FDT_PROP) {
        return NULL;
    }

    uint32_t len = FDT_ALIGN(to_little_endian(property[1]));
    const int PROP_HEADER_SIZE = 3 * sizeof(uint32_t);
    uint32_t offset_bytes = PROP_HEADER_SIZE + len;

    return (const uint32_t *)((const char *)property + offset_bytes);
}

const uint32_t *fdt_skip_structure(const uint32_t *structure, const uintptr_t fdt_end) {
    if (to_little_endian(*structure) != FDT_BEGIN_NODE)
        return NULL;

    const uint32_t *token = structure + 1;
    if ((uintptr_t)token >= fdt_end)
        return NULL;

    const char *name = (const char *)token;
    while (*name != '\0') {
        // Safety: Don't run past the end of the blob looking for \0
        if ((uintptr_t)name >= fdt_end)
            return NULL;
        name++;
    }
    name++;

    // Align to 4-bytes for tokens
    token = (const uint32_t *)FDT_ALIGN_PTR(name);

    // Iterate properties and child nodes
    while ((uintptr_t)token < fdt_end) {
        switch (to_little_endian(*token)) {
            case FDT_BEGIN_NODE:
                // Pass fdt_end to recursive call
                token = fdt_skip_structure(token, fdt_end);
                if (!token)
                    return NULL;

                // The returned token points to END_NODE of the child so skip token
                token++;
                break;
            case FDT_PROP:
                token = fdt_skip_property(token);
                if (!token)
                    return NULL;
                break;
            case FDT_NOP:
                token++;
                break;
            case FDT_END_NODE:
                return token;
            case FDT_END:
                return NULL;
            default:
                return NULL;
        }
    }
    return NULL;
}

const uint32_t *fdt_find_property(const struct fdt_header *fdt, const uint32_t *structure, const char *property, const uintptr_t fdt_end) {
    if (!structure)
        return NULL;

    const char *fdt_strings = fdt + to_little_endian(fdt->off_dt_strings);

    const uint32_t *token = structure;
    while ((uintptr_t)token < fdt_end) {
        switch (*token) {
            case FDT_PROP:
                uint32_t len = to_little_endian(token[1]);
                uint32_t nameoff = to_little_endian(token[2]);
                const char *name = fdt_strings + nameoff;
                if (fdt_node_name_eq(property, name))
                    return token;

                token = FDT_ALIGN_PTR(((const char *)(token + 3)) + len);
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

const uint32_t *fdt_find_subnode(const uint32_t *parent, const uintptr_t fdt_end, const char *target_name) {
    if (to_little_endian(*parent) != FDT_BEGIN_NODE)
        return NULL;

    const uint32_t *token = parent + 1;
    if ((uintptr_t)token >= fdt_end) return NULL;

    const char *name = (const char *)token;
    while (*name != '\0') {
        if ((uintptr_t)name >= fdt_end) return NULL;
        name++;
    }
    // Align token to next 4 bytes (skip null terminator)
    token = (const uint32_t *)FDT_ALIGN_PTR(name + 1);

    while ((uintptr_t)token < fdt_end) {
        switch (to_little_endian(*token)) {
            case FDT_BEGIN_NODE:
                const char *child_name = (const char *)(token + 1);

                const char *ptr_check = child_name;
                // Check 'name' doesn't overrun bounds
                while (*ptr_check != '\0') {
                     if ((uintptr_t)ptr_check >= fdt_end)
                         return NULL;
                     ptr_check++;
                }

                if (fdt_node_name_eq(child_name, target_name)) {
                    return token;
                }

                token = fdt_skip_structure(token, fdt_end);
                if (!token)
                    return NULL;
                token++;
                break;
            case FDT_PROP:
                token = fdt_skip_property(token);
                if (!token)
                    return NULL;
                break;
            case FDT_NOP:
                token++;
                break;
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
    const uintptr_t fdt_end = (const uintptr_t)(fdt + (to_little_endian(fdt->totalsize)));
    const uint32_t *memory_block = fdt_find_structure(fdt, "memory", fdt_end);
    if (memory_block == NULL)
        return;
    const uint32_t *property = fdt_find_property(fdt, memory_block, "reg", fdt_end);
    if (property == NULL)
        return;

    return;
}