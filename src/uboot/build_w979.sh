#!/bin/bash

export ARCH=arm
#export CROSS_COMPILE=$(pwd)/../ext-toolchain/bin/arm-linux-gnueabihf-
export CROSS_COMPILE=$(pwd)/../../output/host/bin/arm-linux-gnueabihf-


make distclean;
make  mx6c403m506_w979_defconfig 
make -j16

cp ./u-boot.imx ./u-boot-imx6qc403-W979H2KBVX2I.imx


