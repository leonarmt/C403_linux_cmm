#!/bin/bash

export ARCH=arm
#export CROSS_COMPILE=$(pwd)/../ext-toolchain/bin/arm-linux-gnueabihf-
export CROSS_COMPILE=$(pwd)/../../output/host/bin/arm-buildroot-linux-uclibcgnueabihf-

make distclean
make  mx6c403rainbowc_defconfig 
make -j8

cp ./u-boot.imx ./u-boot-imx6qc403rc.imx
