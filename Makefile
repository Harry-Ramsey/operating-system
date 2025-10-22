include ./common.mk

.PHONY: all kernel clean run debug

all: kernel

kernel:
	@echo ">>> Building the kernel..."
	@$(MAKE) -C $(KERNEL_DIR) all

clean:
	@echo ">>> Cleaning build artifacts..."
	@$(MAKE) -C $(KERNEL_DIR) clean
	@rm -rf $(BUILD_DIR) $(ELF_FILE)

run: kernel
	@echo ">>> Running kernel in QEMU..."
	qemu-system-aarch64 -M virt -cpu cortex-a53 -kernel $(KERNEL_DIR)/kernel.elf

debug: kernel
	@echo ">>> Running kernel in QEMU (debug mode)..."
	qemu-system-aarch64 -M virt,secure=on -smp 1 -m 1G -cpu cortex-a53 -kernel $(KERNEL_DIR)/kernel.elf -s -S
