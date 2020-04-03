#!/bin/bash
export ARCH=arm
#export CROSS_COMPILE=$(pwd)/../ext-toolchain/bin/arm-linux-gnueabihf-
export CROSS_COMPILE=$(pwd)/../../output/host/bin/arm-buildroot-linux-uclibcgnueabihf-
make distclean;
make imx_v7_defconfig #imx_v7_mfg_defconfig #imx_v7_defconfig  #mx6ul_14x14_lpddr2_arm2_defconfig
make -j8

rm zImage
rm *.dtb
cp arch/arm/boot/zImage ./

#cp arch/arm/boot/dts/imx6ul-armt-s607.dtb ./zImage-imx6ul-s607-emmc.dtb
#cp arch/arm/boot/dts/imx6ul-armt-s707.dtb ./zImage-imx6ul-s707-emmc.dtb

#cp arch/arm/boot/dts/imx6q-c403-W97BH2LBVX2I.dtb ./zImage-imx6q-c403-W97BH2LBVX2I.dtb
#cp arch/arm/boot/dts/imx6q-c403-W97AH2KBVX2I.dtb ./zImage-imx6q-c403-W97AH2KBVX2I.dtb
#cp arch/arm/boot/dts/imx6q-c403-W979H2KBVX2I.dtb ./zImage-imx6q-c403-W979H2KBVX2I.dtb

#cp arch/arm/boot/dts/imx6q-c403m704.dtb ./zImage-imx6q-c403-2gb-m704.dtb

cp arch/arm/boot/dts/imx6q-c403m506.dtb ./zImage-imx6q-c403-2gb-m506.dtb
