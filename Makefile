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
	@echo ">>> Running kernel on ARM FVP..."
	$(FVP_MODEL_PATH) -C bp.flashloader0.fname="" -C bp.flashloader1.fname="" -C bp.secureflashloader.fname="" -C cluster0.NUM_CORES=1 -C bp.secure_memory=0 -C bp.vis.disable_visualisation=1 -a $(KERNEL_DIR)/kernel.elf

