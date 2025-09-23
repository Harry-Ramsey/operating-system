# Set the architecture to aarch64 to resolve any potential mismatches
set architecture aarch64

# Connect to the GDB server running on QEMU
target remote localhost:1234

# Load the symbol file at the correct memory address (QEMU's base address for the virt machine)
file kernel.elf

# Set a breakpoint at the program's entry point
break _start
