# Kernel Makefile

include ../common.mk

SRC_DIR := src
INCLUDE_DIR := include

CFLAGS += -I$(INCLUDE_DIR) -g
ASMFLAGS += -I$(INCLUDE_DIR) -g

C_SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
C_SRC_FILES += $(wildcard $(SRC_DIR)/*/*.c)
ASM_SRC_FILES := $(wildcard $(SRC_DIR)/*.S)
ASM_SRC_FILES += $(wildcard $(SRC_DIR)/utils/*.S)

LINKER_FILE = $(SRC_DIR)/linker.ld -g

C_OBJ_FILES := $(C_SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
ASM_OBJ_FILES := $(ASM_SRC_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)
OBJ_FILES := $(C_OBJ_FILES) $(ASM_OBJ_FILES)

.PHONY: all clean

all: $(ELF_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/utils $(BUILD_DIR)/console

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(ASMFLAGS) -c $< -o $@

$(ELF_FILE): $(OBJ_FILES)
	$(LD) $(LDFLAGS) -T $(LINKER_FILE) -o $@ $(OBJ_FILES)

clean:
	rm -rf $(BUILD_DIR) $(ELF_FILE)
