#include <stdint.h>

volatile uint8_t *uart_base = (uint8_t *) 0x09000000;

// UART register offsets
#define UART_CR     (*((volatile uint32_t *)(uart_base + 0x30)))
#define UART_LCR_H  (*((volatile uint32_t *)(uart_base + 0x2c)))
#define UART_FR     (*((volatile uint32_t *)(uart_base + 0x18)))

void uart_init(void) {
    // Disable UART first
    UART_CR = 0;
    // Enable FIFO, 8 data bits, no parity
    UART_LCR_H = (1 << 4) | (1 << 5) | (1 << 6);
    // Enable UART, TX, and RX
    UART_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

void putchar(char c) {
    // Wait until the transmit FIFO is not full
    while ((UART_FR & (1 << 5)) != 0);
    *(volatile uint8_t *)(uart_base + 0x00) = c;
}

void print(const char *s) {
    while(*s != '\0') {
        putchar(*s);
        s++;
    }
}

int main(int argc, char **argv) {
    uart_init();
    print("Hello world\n");
    return 0;
}
