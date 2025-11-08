#include <stdint.h>

#include "console/uart.h"

int main(int argc, char **argv) {
    uart_init();
    uart_puts("Hello world\n");
    return 0;
}

