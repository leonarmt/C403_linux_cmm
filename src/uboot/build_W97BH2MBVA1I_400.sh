#!/bin/bash

export ARCH=arm
export CROSS_COMPILE=$(pwd)/../ext-toolchain/bin/arm-linux-gnueabihf-

make distclean;
make  mx6c403m506_W97BH2MBVA1I_400_defconfig 
make -j16

cp ./u-boot.imx ./u-boot-imx6qc403-W97BH2LBVX2I.imx


