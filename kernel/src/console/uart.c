#include "console/uart.h"
#include <stdint.h>

void uart_init() {
    volatile uint32_t *uart_base = (uint32_t *)UART_BASE;
    volatile uint32_t *uart_fr = (uint32_t *)UART_FR;
    volatile uint32_t *uart_lcr_h = (uint32_t*)UART_LCR_H;
    volatile uint32_t *uart_cr = (uint32_t *)UART_CR;

    // Disable UART first
    *uart_cr = 0;
    // Enable FIFO, 8 data bits, no parity
    *uart_lcr_h = (1 << 4) | (1 << 5) | (1 << 6);
    // Enable UART, TX, and RX
    *uart_cr = (1 << 0) | (1 << 8) | (1 << 9);
}

void uart_putc(const char c) {
    // Wait until the transmit FIFO is not full
    while ((UART_FR & (1 << 5)) != 0);
    *(volatile uint8_t *)(UART_BASE + 0x00) = c;
}

void uart_puts(const char *s) {
    while(*s != '\0') {
        uart_putc(*s);
        s++;
    }
}

