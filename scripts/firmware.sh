#!/bin/bash
mkdir firmware
pushd firmware
FIRMWARE_DIR="$PWD"

git clone git@github.com:ARM-software/arm-trusted-firmware.git
git clone git@github.com:u-boot/u-boot.git

pushd u-boot
make HOSTCC=clang CROSS_COMPILE=aarch64-linux-gnu- CC=clang vexpress_aemv8a_semi_defconfig
make HOSTCC=clang CROSS_COMPILE=aarch64-linux-gnu- CC=clang -j$(nproc)
popd

pushd arm-trusted-firmware
make CC=clang PLAT=fvp BL33="$FIRMWARE_DIR/u-boot/u-boot.bin" fiptool all fip
popd