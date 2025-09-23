# Kernel Makefile

include ../common.mk

SRC_DIR := src

C_SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
ASM_SRC_FILES := $(wildcard $(SRC_DIR)/*.S)

LINKER_FILE = $(SRC_DIR)/linker.ld

C_OBJ_FILES := $(C_SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
ASM_OBJ_FILES := $(ASM_SRC_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
OBJ_FILES := $(C_OBJ_FILES) $(ASM_OBJ_FILES)

.PHONY: all clean

all: $(ELF_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(ASMFLAGS) -c $< -o $@

$(ELF_FILE): $(OBJ_FILES)
	$(LD) $(LDFLAGS) -T $(LINKER_FILE) -o $@ $(OBJ_FILES)

clean:
	rm -rf $(BUILD_DIR) $(ELF_FILE)
