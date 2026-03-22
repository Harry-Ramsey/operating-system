#include "console/console.h"
#include "console/uart.h"

void print_to_consoles(const char *message) {
    uart_puts(message);
}
