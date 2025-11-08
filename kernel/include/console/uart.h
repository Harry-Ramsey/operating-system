#ifndef UART_H
#define UART_H

#include <stdint.h>

#define UART_BASE   0x09000000
#define UART_CR     (UART_BASE + 0x30)
#define UART_LCR_H  (UART_BASE + 0x2c)
#define UART_FR     (UART_BASE + 0x18)

void uart_init();
void uart_putc(const char c);
void uart_puts(const char *s);
void uart_puthex(uint64_t v);

#endif /* UART_H */
