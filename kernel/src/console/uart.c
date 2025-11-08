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

void uart_puthex(uint64_t v) {
    uart_puts("0x");

    if (v == 0)
        uart_puts("00");

    while (v > 0) {
        uint64_t remainder = v % 16;
        switch(remainder) {
            case 10:
                uart_putc('A');
                break;
            case 11:
                uart_putc('B');
                break;
            case 12:
                uart_putc('C');
                break;
            case 13:
                uart_putc('D');
                break;
            case 14:
                uart_putc('E');
                break;
            case 15:
                uart_putc('F');
                break;
            default:
                uart_putc((char)(remainder + 48));
        }

        v /= 16;
    }


}
