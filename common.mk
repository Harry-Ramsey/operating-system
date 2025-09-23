# Makefile toolchain for AArch64 bare-metal kernel
CC       := clang
LD       := ld.lld
OBJCOPY  := llvm-objcopy
TARGET   := aarch64-none-elf

# Directories and files
BUILD_DIR := build
KERNEL_DIR := kernel
TOPLEVEL_DIR := $(CURDIR)
ELF_FILE := $(TOPLEVEL_DIR)/kernel.elf

# Common flags
CFLAGS   = --target=$(TARGET)
ASMFLAGS = --target=$(TARGET)
LDFLAGS  = -L
