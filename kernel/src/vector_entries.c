#include "vector_entries.h"
#include <stdint.h>

#include "console/uart.h"

void exception_not_implemented() {
    uint64_t fault_address;
    uint64_t exception_syndrome;
    asm("mrs %[address], far_el1\n"
        "mrs %[exception], esr_el1\n"
        : [address] "=r" (fault_address),
          [exception] "=r" (exception_syndrome)
    );
    uart_puts("FAR_EL1: ");
    uart_puthex(fault_address);
    uart_puts("\r\nESR_EL1: ");
    uart_puthex(exception_syndrome);
    while(1) { }
}

