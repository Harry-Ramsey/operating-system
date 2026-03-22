#include <stdint.h>

#include "console/uart.h"
#include "stdlib/stdio.h"

int main(int argc, char **argv) {
    uart_init();
    printf("Hello world\n");
    return 0;
}

