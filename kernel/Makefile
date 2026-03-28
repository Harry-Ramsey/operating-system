# Kernel Makefile

include ../common.mk

SRC_DIR := src
INCLUDE_DIR := include

TARGET := aarch64-unknown-windows

CFLAGS += -I$(INCLUDE_DIR) -g --target=$(TARGET)
ASMFLAGS += -I$(INCLUDE_DIR) -g --target=$(TARGET)
LDFLAGS += -flavor link -subsystem:efi_application -entry:EfiMain

C_SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
C_SRC_FILES += $(wildcard $(SRC_DIR)/*/*.c)
ASM_SRC_FILES := $(wildcard $(SRC_DIR)/*.S)
ASM_SRC_FILES += $(wildcard $(SRC_DIR)/utils/*.S)

C_OBJ_FILES := $(C_SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
ASM_OBJ_FILES := $(ASM_SRC_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
OBJ_FILES := $(C_OBJ_FILES) $(ASM_OBJ_FILES)

.PHONY: all clean

all: $(EFI_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/utils $(BUILD_DIR)/console $(BUILD_DIR)/stdlib

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(ASMFLAGS) -c $< -o $@

$(EFI_FILE): $(OBJ_FILES)
	$(LD) $(LDFLAGS) -out:$@ $(OBJ_FILES)

clean:
	rm -rf $(BUILD_DIR) $(EFI_FILE)
