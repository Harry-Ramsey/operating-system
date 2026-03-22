#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

#include "console/console.h"
#include "console/uart.h"
#include "stdlib/stdio.h"

static void reverse(char *start, char *end) {
    while (start < end) {
        char tmp = *start;
        *start++ = *end;
        *end-- = tmp;
    }
}

char *octal_to_ascii(unsigned int value, char *buffer) {
    int i = 0;
    buffer[i++] = '0'; // optional prefix

    // Digits are written in reverse order
    do {
        buffer[i++] = '0' + (value & 0x7);
        value >>= 3;
    } while (value);

    // Reverse only the digit portion
    reverse(buffer + 1, buffer + i - 1);

    buffer[i] = '\0';
    return buffer;
}

char *pointer_to_ascii(const void *pointer, char *buffer) {
    const char *hex = "0123456789abcdef";
    uintptr_t value = (uintptr_t)pointer;

    int i = 0;
    buffer[i++] = '0';
    buffer[i++] = 'x';

    // Digits are written in reverse order
    do {
        buffer[i++] = hex[value & 0xF];
        value >>= 4;
    } while (value);

    // Reverse only the digit portion
    reverse(buffer + 2, buffer + i - 1);

    buffer[i] = '\0';
    return buffer;
}

char *unsigned_to_ascii(unsigned int value, char *buffer, int base) {
    int i = 0;
    if (base < 2 || base > 36) {
        buffer[0] = '\0';
        return buffer;
    }

    // Digits are written in reverse order
    do {
        unsigned int digit = value % base;
        buffer[i++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
        value /= base;
    } while (value);

    buffer[i] = '\0';

    // Reverse only the digit portion
    reverse(buffer, buffer + i - 1);

    return buffer;
}

char *integer_to_ascii(int value, char *buffer, int base) {
    if (base < 2 || base > 36) {
        buffer[0] = '\0';
        return buffer;
    }

    if (value < 0 && base == 10) {
        buffer[0] = '-';

        // Convert safely to unsigned to avoid overflow on INT_MIN
        unsigned int u = (unsigned int)(-(value + 1)) + 1;

        unsigned_to_ascii(u, buffer + 1, base);
        return buffer;
    }

    return unsigned_to_ascii((unsigned int)value, buffer, base);
}

static int print_and_count(const char *message) {
    int length = 0;

    while (message[length] != '\0') {
        length++;
    }

    print_to_consoles(message);
    return length;
}

int printf(const char *format, ...) {
    va_list args;
    char format_buffer[65];
    int characters_written = 0;

    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;

            if (*format == '\0') {
                characters_written += print_and_count("%");
                break;
            }

            switch (*format) {
                case 'i':
                case 'd': {
                    int arg = va_arg(args, int);
                    integer_to_ascii(arg, format_buffer, 10);
                    characters_written += print_and_count(format_buffer);
                    break;
                }
                case 'u': {
                    unsigned int arg = va_arg(args, unsigned int);
                    unsigned_to_ascii(arg, format_buffer, 10);
                    characters_written += print_and_count(format_buffer);
                    break;
                }
                case 'x':
                case 'X': {
                    unsigned int arg = va_arg(args, unsigned int);
                    unsigned_to_ascii(arg, format_buffer, 16);
                    characters_written += print_and_count(format_buffer);
                    break;
                }
                case 'o': {
                    unsigned int arg = va_arg(args, unsigned int);
                    octal_to_ascii(arg, format_buffer);
                    characters_written += print_and_count(format_buffer);
                    break;
                }
                case 'p': {
                    const void *arg = va_arg(args, const void *);
                    pointer_to_ascii(arg, format_buffer);
                    characters_written += print_and_count(format_buffer);
                    break;
                }
                case 'c': {
                    char arg = (char)(va_arg(args, int));
                    uart_putc(arg);
                    characters_written++;
                    break;
                }
                case 's': {
                    const char *arg = va_arg(args, const char *);
                    characters_written += print_and_count(arg != NULL ? arg : "(null)");
                    break;
                }
                case '%': {
                    format_buffer[0] = '%';
                    format_buffer[1] = '\0';
                    characters_written += print_and_count(format_buffer);
                    break;
                }
                default: {
                    format_buffer[0] = '%';
                    format_buffer[1] = *format;
                    format_buffer[2] = '\0';
                    characters_written += print_and_count(format_buffer);
                    break;
                }
            }

            format++;
        } else {
            format_buffer[0] = *format++;
            format_buffer[1] = '\0';
            characters_written += print_and_count(format_buffer);
        }
    }

    va_end(args);
    return characters_written;
}
