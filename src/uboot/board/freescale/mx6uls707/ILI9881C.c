#include <asm/arch/clock.h>
#include <asm/arch/iomux.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/mx6ul_pins.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>
#include <asm/imx-common/iomux-v3.h>
#include <asm/imx-common/boot_mode.h>
#include <asm/imx-common/mxc_i2c.h>
#include <asm/io.h>
#include <common.h>
#include <fsl_esdhc.h>
#include <i2c.h>
#include <miiphy.h>
#include <linux/sizes.h>
#include <mmc.h>
#include <mxsfb.h>
#include <netdev.h>
#include <power/pmic.h>
#include <power/pfuze3000_pmic.h>
#include "../common/pfuze.h"
#include <usb.h>
#include <usb/ehci-fsl.h>
#include <asm/imx-common/video.h>
#include "ssd2828.h"
#include "ILI9881C.h"
  

int ILI9881C_init(void)
{
	ssd2828_gpio_init();
	ssd2828_reset();
	SPI_READ_ID();

		//SSD2825_Initial
							W_C(0xb7);
							W_D(0x50);//50=TX_CLK 70=PCLK
							W_D(0x00);	 //Configuration Register
	
							W_C(0xb8);
							W_D(0x00);
							W_D(0x00);	 //VC(Virtual ChannelID) Control Register
	
							W_C(0xb9);
							W_D(0x00);//1=PLL disable
							W_D(0x00);
									   //TX_CLK/MS should be between 5Mhz to100Mhz
							W_C(0xBA);//PLL=(TX_CLK/MS)*NS 8228=480M 4428=240M	061E=120M 4214=240M 821E=360M 8219=300M
							W_D(0x12);//D7-0=NS(0x01 : NS=1)
							W_D(0x42);//D15-14=PLL·¶Î§ 00=62.5-125 01=126-250 10=251-500 11=501-1000  DB12-8=MS(01:MS=1)
	
							W_C(0xBB);//LP Clock Divider LP clock = 400MHz / LPD / 8 = 240 / 8 / 4 = 7.5MHz
							W_D(0x03);//D5-0=LPD=0x1 \u0161C Divide by 2
							W_D(0x00);
	
							W_C(0xb9);
							W_D(0x01);//1=PLL disable
							W_D(0x00);
							//MIPI lane configuration
									W_C(0xDE);//Í\u0161µÀÊý
									W_D(0x00);//11=4LANE 10=3LANE 01=2LANE 00=1LANE
									W_D(0x00);
	
							W_C(0xc9);
							W_D(0x02);
							W_D(0x23);	 //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
							mdelay(100);
	//-------
	
		//LCD driver initialization
		W_C(0xB7);
		W_D(0x10);//10=TX_CLK 30=PCLK
		W_D(0x02);
	
		W_C(0xBD);
		W_D(0x00);
		W_D(0x00);
		
#if 1
	
	GP_COMMAD_PA(4);
	W_D(0xFF);
	W_D(0x98);
	W_D(0x81);
	W_D(0x03);
	
	
	
	// Set Power
		GP_COMMAD_PA(2);W_D(0x01);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x02);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x03);W_D(0x73);
		GP_COMMAD_PA(2);W_D(0x04);W_D(0xD3);
		GP_COMMAD_PA(2);W_D(0x05);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x06);W_D(0x0A);
		GP_COMMAD_PA(2);W_D(0x07);W_D(0x0F);
		GP_COMMAD_PA(2);W_D(0x08);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x09);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x0A);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x0B);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x0C);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x0D);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x0E);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x0F);W_D(0x19);
		GP_COMMAD_PA(2);W_D(0x10);W_D(0x19);
		GP_COMMAD_PA(2);W_D(0x11);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x12);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x13);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x14);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x15);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x16);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x17);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x18);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x19);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x1A);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x1B);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x1C);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x1D);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x1E);W_D(0x40);
		GP_COMMAD_PA(2);W_D(0x1F);W_D(0x80);
		GP_COMMAD_PA(2);W_D(0x20);W_D(0x06);
		GP_COMMAD_PA(2);W_D(0x21);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x22);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x23);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x24);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x25);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x26);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x27);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x28);W_D(0x33);
		GP_COMMAD_PA(2);W_D(0x29);W_D(0x03);
		GP_COMMAD_PA(2);W_D(0x2A);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x2B);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x2C);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x2D);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x2E);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x2F);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x30);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x31);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x32);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x33);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x34);W_D(0x03);
		GP_COMMAD_PA(2);W_D(0x35);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x36);W_D(0x03);
		GP_COMMAD_PA(2);W_D(0x37);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x38);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x39);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x3A);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x3B);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x3C);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x3D);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x3E);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x3F);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x40);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x41);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x42);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x43);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x44);W_D(0x00);
	
		
		GP_COMMAD_PA(2);W_D(0x50);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x51);W_D(0x23);
		GP_COMMAD_PA(2);W_D(0x52);W_D(0x45);
		GP_COMMAD_PA(2);W_D(0x53);W_D(0x67);
		GP_COMMAD_PA(2);W_D(0x54);W_D(0x89);
		GP_COMMAD_PA(2);W_D(0x55);W_D(0xAB);
		GP_COMMAD_PA(2);W_D(0x56);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x57);W_D(0x23);
		GP_COMMAD_PA(2);W_D(0x58);W_D(0x45);
		GP_COMMAD_PA(2);W_D(0x59);W_D(0x67);
		GP_COMMAD_PA(2);W_D(0x5A);W_D(0x89);
		GP_COMMAD_PA(2);W_D(0x5B);W_D(0xAB);
		GP_COMMAD_PA(2);W_D(0x5C);W_D(0xCD);
		GP_COMMAD_PA(2);W_D(0x5D);W_D(0xEF);
		GP_COMMAD_PA(2);W_D(0x5E);W_D(0x11);
		GP_COMMAD_PA(2);W_D(0x5F);W_D(0x08);
		
		GP_COMMAD_PA(2);W_D(0x60);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x61);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x62);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x63);W_D(0x0D);
		GP_COMMAD_PA(2);W_D(0x64);W_D(0x0C);
		GP_COMMAD_PA(2);W_D(0x65);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x66);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x67);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x68);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x69);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x6A);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x6B);W_D(0x0F);
		GP_COMMAD_PA(2);W_D(0x6C);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x6D);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x6E);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x6F);W_D(0x02);
		
		GP_COMMAD_PA(2);W_D(0x70);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x71);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x72);W_D(0x0E);
		GP_COMMAD_PA(2);W_D(0x73);W_D(0x06);
		GP_COMMAD_PA(2);W_D(0x74);W_D(0x07);
		GP_COMMAD_PA(2);W_D(0x75);W_D(0x08);
		GP_COMMAD_PA(2);W_D(0x76);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x77);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x78);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x79);W_D(0x0D);
		GP_COMMAD_PA(2);W_D(0x7A);W_D(0x0C);
		GP_COMMAD_PA(2);W_D(0x7B);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x7C);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x7D);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x7E);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x7F);W_D(0x02);
		
		GP_COMMAD_PA(2);W_D(0x80);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x81);W_D(0x0F);
		GP_COMMAD_PA(2);W_D(0x82);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x83);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x84);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x85);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x86);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x87);W_D(0x02);
		GP_COMMAD_PA(2);W_D(0x88);W_D(0x0E);
		GP_COMMAD_PA(2);W_D(0x89);W_D(0x06);
		GP_COMMAD_PA(2);W_D(0x8A);W_D(0x07);
		
		GP_COMMAD_PA(4);W_D(0xFF);W_D(0x98);W_D(0x81);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x2E);W_D(0x50);
			
		
		GP_COMMAD_PA(4);W_D(0xFF);W_D(0x98);W_D(0x81);W_D(0x04);
		GP_COMMAD_PA(2);W_D(0x6C);W_D(0x15);
		GP_COMMAD_PA(2);W_D(0x6E);W_D(0x2A);
		GP_COMMAD_PA(2);W_D(0x6F);W_D(0x33);
		GP_COMMAD_PA(2);W_D(0x3A);W_D(0xA4);
		GP_COMMAD_PA(2);W_D(0x8D);W_D(0x15);
		GP_COMMAD_PA(2);W_D(0x87);W_D(0xBA);
		GP_COMMAD_PA(2);W_D(0x26);W_D(0x76);
		GP_COMMAD_PA(2);W_D(0xB2);W_D(0xD1);
		GP_COMMAD_PA(2);W_D(0x00);W_D(0x00);
		 
	  
		GP_COMMAD_PA(4);W_D(0xFF);W_D(0x98);W_D(0x81);W_D(0x01);
		GP_COMMAD_PA(2);W_D(0x22);W_D(0x0A);
		GP_COMMAD_PA(2);W_D(0x53);W_D(0x57);
		GP_COMMAD_PA(2);W_D(0x55);W_D(0x61);
		GP_COMMAD_PA(2);W_D(0x50);W_D(0x9F);
		GP_COMMAD_PA(2);W_D(0x51);W_D(0x9A);
		GP_COMMAD_PA(2);W_D(0x31);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0x60);W_D(0x0C);
		
		GP_COMMAD_PA(2);W_D(0xA0);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0xA1);W_D(0x22);
		GP_COMMAD_PA(2);W_D(0xA2);W_D(0x32);
		GP_COMMAD_PA(2);W_D(0xA3);W_D(0x13);
		GP_COMMAD_PA(2);W_D(0xA4);W_D(0x17);
		GP_COMMAD_PA(2);W_D(0xA5);W_D(0x2B);
		GP_COMMAD_PA(2);W_D(0xA6);W_D(0x1F);
		GP_COMMAD_PA(2);W_D(0xA7);W_D(0x1F);
		GP_COMMAD_PA(2);W_D(0xA8);W_D(0xAD);
		GP_COMMAD_PA(2);W_D(0xA9);W_D(0x1E);
		GP_COMMAD_PA(2);W_D(0xAA);W_D(0x29);
		GP_COMMAD_PA(2);W_D(0xAB);W_D(0x9D);
		GP_COMMAD_PA(2);W_D(0xAC);W_D(0x1D);
		GP_COMMAD_PA(2);W_D(0xAD);W_D(0x1B);
		GP_COMMAD_PA(2);W_D(0xAE);W_D(0x4F);
		GP_COMMAD_PA(2);W_D(0xAF);W_D(0x22);
		
		GP_COMMAD_PA(2);W_D(0xB0);W_D(0x2A);
		GP_COMMAD_PA(2);W_D(0xB1);W_D(0x5A);
		GP_COMMAD_PA(2);W_D(0xB2);W_D(0x67);
		GP_COMMAD_PA(2);W_D(0xB3);W_D(0x3F);
		
		GP_COMMAD_PA(2);W_D(0xC0);W_D(0x00);
		GP_COMMAD_PA(2);W_D(0xC1);W_D(0x22);
		GP_COMMAD_PA(2);W_D(0xC2);W_D(0x33);
		GP_COMMAD_PA(2);W_D(0xC3);W_D(0x13);
		GP_COMMAD_PA(2);W_D(0xC4);W_D(0x17);
		GP_COMMAD_PA(2);W_D(0xC5);W_D(0x2B);
		GP_COMMAD_PA(2);W_D(0xC6);W_D(0x1F);
		GP_COMMAD_PA(2);W_D(0xC7);W_D(0x1F);
		GP_COMMAD_PA(2);W_D(0xC8);W_D(0xAD);
		GP_COMMAD_PA(2);W_D(0xC9);W_D(0x1E);
		GP_COMMAD_PA(2);W_D(0xCA);W_D(0x29);
		GP_COMMAD_PA(2);W_D(0xCB);W_D(0x9D);
		GP_COMMAD_PA(2);W_D(0xCC);W_D(0x1D);
		GP_COMMAD_PA(2);W_D(0xCD);W_D(0x1B);
		GP_COMMAD_PA(2);W_D(0xCE);W_D(0x4F);
		GP_COMMAD_PA(2);W_D(0xCF);W_D(0x22);
		
		GP_COMMAD_PA(2);W_D(0xD0);W_D(0x2A);
		GP_COMMAD_PA(2);W_D(0xD1);W_D(0x5A);
		GP_COMMAD_PA(2);W_D(0xD2);W_D(0x67);
		GP_COMMAD_PA(2);W_D(0xD3);W_D(0x3F);
		
		
		
		
		
		GP_COMMAD_PA(4);W_D(0xFF);W_D(0x98);W_D(0x81);W_D(0x00);
	
	
	   GP_COMMAD_PA(1); 
	   W_D(0x11);
	   mdelay(150);
	
	   GP_COMMAD_PA(1); 
	   W_D(0x29);
	   mdelay(50);
	
#else  
	//===================================================Video Mode Initial Code
	
				 //////////////////////////////////////////////////////////////////////
								W_C(0xB7);
								W_D(0x50);//10=TX_CLK 30=PCLK
								W_D(0x02);
	
								W_C(0xBD);
								W_D(0x00);
								W_D(0x00);
	
	///////////////////////////////////////////
	
	//****************************************************************************//
	//****************************** Page 1 Command ******************************//
	//****************************************************************************//
	GP_COMMAD_PA(6);W_D(0xFF);W_D(0xFF);W_D(0x98);W_D(0x06);W_D(0x04);W_D(0x01);	// Change to Page 1
	
	GP_COMMAD_PA(2);W_D(0x08);W_D(0x10);				// output SDA
	
	GP_COMMAD_PA(2);W_D(0x21);W_D(0x01);				// DE = 1 Active
	
	GP_COMMAD_PA(2);W_D(0x30);W_D(0x01);				 // 480 X 854
	
	GP_COMMAD_PA(2);W_D(0x31);W_D(0x02);				// 2-dot Inversion
	
	GP_COMMAD_PA(2);W_D(0x60);W_D(0x07);				 // SDTI
	
	GP_COMMAD_PA(2);W_D(0x61);W_D(0x06);			   // CRTI
	
	GP_COMMAD_PA(2);W_D(0x62);W_D(0x06);				 // EQTI
	
	GP_COMMAD_PA(2);W_D(0x63);W_D(0x04);				// PCTI
	
	GP_COMMAD_PA(2);W_D(0x40);W_D(0x14);				// BT  +2.5/-2.5 pump for DDVDH-L
	
	GP_COMMAD_PA(2);W_D(0x41);W_D(0x22);				 // DVDDH DVDDL clamp  
	
	GP_COMMAD_PA(2);W_D(0x42);W_D(0x02);				 // VGH/VGL  01
	
	GP_COMMAD_PA(2);W_D(0x43);W_D(0x84);				 // VGH/VGL 0x89:VGH 15V
	
	GP_COMMAD_PA(2);W_D(0x44);W_D(0x8A);				// VGH/VGL 
	
	GP_COMMAD_PA(2);W_D(0x50);W_D(0x78);				 // VGMP
	
	GP_COMMAD_PA(2);W_D(0x51);W_D(0x78);				 // VGMN
	
	GP_COMMAD_PA(2);W_D(0x52);W_D(0x00);				 //Flicker
	
	GP_COMMAD_PA(2);W_D(0x53);W_D(0x4B);				//Flicker 
	
	GP_COMMAD_PA(2);W_D(0x54);W_D(0x00);				 //Flicker 36H=03Ê±µ÷VCOM
	
	GP_COMMAD_PA(2);W_D(0x55);W_D(0x4B);				//Flicker 36H=03Ê±µ÷VCOM
	
	//++++++++++++++++++ Gamma Setting ++++++++++++++++++//
	GP_COMMAD_PA(2);W_D(0xA0);W_D(0x00); // Gamma 0 
	
	GP_COMMAD_PA(2);W_D(0xA1);W_D(0x19);  // Gamma 4 
	
	GP_COMMAD_PA(2);W_D(0xA2);W_D(0x20);  // Gamma 8
	
	GP_COMMAD_PA(2);W_D(0xA3);W_D(0x0E);  // Gamma 16
	
	GP_COMMAD_PA(2);W_D(0xA4);W_D(0x06);  // Gamma 24
	
	GP_COMMAD_PA(2);W_D(0xA5);W_D(0x09);  // Gamma 52
	
	GP_COMMAD_PA(2);W_D(0xA6);W_D(0x06); // Gamma 80
	
	GP_COMMAD_PA(2);W_D(0xA7);W_D(0x05);  // Gamma 108
	
	GP_COMMAD_PA(2);W_D(0xA8);W_D(0x07);  // Gamma 147
	
	GP_COMMAD_PA(2);W_D(0xA9);W_D(0x0B);  // Gamma 175
	
	GP_COMMAD_PA(2);W_D(0xAA);W_D(0x12);  // Gamma 203
	
	GP_COMMAD_PA(2);W_D(0xAB);W_D(0x07);  // Gamma 231
	
	GP_COMMAD_PA(2);W_D(0xAC);W_D(0x0E);  // Gamma 239
	
	GP_COMMAD_PA(2);W_D(0xAD);W_D(0x15);  // Gamma 247
	
	GP_COMMAD_PA(2);W_D(0xAE);W_D(0x0C);  // Gamma 251
	
	GP_COMMAD_PA(2);W_D(0xAF);W_D(0x00);  // Gamma 255
	
	
	GP_COMMAD_PA(2);W_D(0xC0);W_D(0x00); // Gamma 0 
	
	GP_COMMAD_PA(2);W_D(0xC1);W_D(0x19);  // Gamma 4
	
	GP_COMMAD_PA(2);W_D(0xC2);W_D(0x20);  // Gamma 8
	
	GP_COMMAD_PA(2);W_D(0xC3);W_D(0x0E);  // Gamma 16
	
	GP_COMMAD_PA(2);W_D(0xC4);W_D(0x06);  // Gamma 24
	
	GP_COMMAD_PA(2);W_D(0xC5);W_D(0x09);  // Gamma 52
	
	GP_COMMAD_PA(2);W_D(0xC6);W_D(0x06);  // Gamma 80
	
	GP_COMMAD_PA(2);W_D(0xC7);W_D(0x04);  // Gamma 108
	
	GP_COMMAD_PA(2);W_D(0xC8);W_D(0x07);  // Gamma 147
	
	GP_COMMAD_PA(2);W_D(0xC9);W_D(0x0B);  // Gamma 175
	
	GP_COMMAD_PA(2);W_D(0xCA);W_D(0x12);  // Gamma 203
	
	GP_COMMAD_PA(2);W_D(0xCB);W_D(0x07); // Gamma 231
	
	GP_COMMAD_PA(2);W_D(0xCC);W_D(0x0E); // Gamma 239
	
	GP_COMMAD_PA(2);W_D(0xCD);W_D(0x15);  // Gamma 247
	
	GP_COMMAD_PA(2);W_D(0xCE);W_D(0x0C);  // Gamma 251
	
	GP_COMMAD_PA(2);W_D(0xCF);W_D(0x00);  // Gamma 255
	
	
	//****************************************************************************//
	//****************************** Page 6 Command ******************************//
	//****************************************************************************//
	GP_COMMAD_PA(6);W_D(0xFF);W_D(0xFF);W_D(0x98);W_D(0x06);W_D(0x04);W_D(0x06);	 // Change to Page 6
	
	GP_COMMAD_PA(2);W_D(0x00);W_D(0x20);
	
	GP_COMMAD_PA(2);W_D(0x01);W_D(0x04);
	
	GP_COMMAD_PA(2);W_D(0x02);W_D(0x00);	
	
	GP_COMMAD_PA(2);W_D(0x03);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x04);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x05);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x06);W_D(0x88);   
	
	GP_COMMAD_PA(2);W_D(0x07);W_D(0x04);
	
	GP_COMMAD_PA(2);W_D(0x08);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x09);W_D(0x90);	
	
	GP_COMMAD_PA(2);W_D(0x0A);W_D(0x03);	
	
	GP_COMMAD_PA(2);W_D(0x0B);W_D(0x01);	
	
	GP_COMMAD_PA(2);W_D(0x0C);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x0D);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x0E);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x0F);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x10);W_D(0x55);
	
	GP_COMMAD_PA(2);W_D(0x11);W_D(0x53);
	
	GP_COMMAD_PA(2);W_D(0x12);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x13);W_D(0x0D);
	
	GP_COMMAD_PA(2);W_D(0x14);W_D(0x0D);
	
	GP_COMMAD_PA(2);W_D(0x15);W_D(0x43);
	
	GP_COMMAD_PA(2);W_D(0x16);W_D(0x0B);
	
	GP_COMMAD_PA(2);W_D(0x17);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x18);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x19);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x1A);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x1B);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x1C);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x1D);W_D(0x00);
	
	
	GP_COMMAD_PA(2);W_D(0x20);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x21);W_D(0x23);
	
	GP_COMMAD_PA(2);W_D(0x22);W_D(0x45);
	
	GP_COMMAD_PA(2);W_D(0x23);W_D(0x67);
	
	GP_COMMAD_PA(2);W_D(0x24);W_D(0x01);
	
	GP_COMMAD_PA(2);W_D(0x25);W_D(0x23);
	
	GP_COMMAD_PA(2);W_D(0x26);W_D(0x45);
	
	GP_COMMAD_PA(2);W_D(0x27);W_D(0x67);
	
	
	GP_COMMAD_PA(2);W_D(0x30);W_D(0x02);
	
	GP_COMMAD_PA(2);W_D(0x31);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x32);W_D(0x11);
	
	GP_COMMAD_PA(2);W_D(0x33);W_D(0xAA);
	
	GP_COMMAD_PA(2);W_D(0x34);W_D(0xBB);
	
	GP_COMMAD_PA(2);W_D(0x35);W_D(0x66);
	
	GP_COMMAD_PA(2);W_D(0x36);W_D(0x00);
	
	GP_COMMAD_PA(2);W_D(0x37);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x38);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x39);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x3A);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x3B);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x3C);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x3D);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x3E);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x3F);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x40);W_D(0x22);
	
	GP_COMMAD_PA(2);W_D(0x52);W_D(0x10); 
	
	GP_COMMAD_PA(2);W_D(0x53);W_D(0x10);				 // 0x10:VGLO tie VGL; 0x12:VGLO tie VGL_REG		   
	
	
	
	GP_COMMAD_PA(6);W_D(0xFF);W_D(0xFF);W_D(0x98);W_D(0x06);W_D(0x04);W_D(0x07);	 // Change to Page 7
	
	GP_COMMAD_PA(2);W_D(0x17);W_D(0x22);				 // 0x22:VGLO tie VGL; 0x32:VGLO tie VGL_REG
	
	GP_COMMAD_PA(2);W_D(0x18);W_D(0x1D);
	
	GP_COMMAD_PA(2);W_D(0x06);W_D(0x13);
	
	GP_COMMAD_PA(2);W_D(0x02);W_D(0x77);				 
	
	GP_COMMAD_PA(2);W_D(0xE1);W_D(0x79);				 
	
	
	//****************************************************************************//
	//****************************** Page 0 Command ******************************//
	//****************************************************************************//
	
	GP_COMMAD_PA(6);W_D(0xFF);W_D(0xFF);W_D(0x98);W_D(0x06);W_D(0x04);W_D(0x00);	 // Change to Page 0
	
	
	
	GP_COMMAD_PA(1);W_D(0x11);
	
	mdelay(120);
	
	GP_COMMAD_PA(1);W_D(0x29);
	mdelay(10);
#endif
	
	
	
	//----------------------
		//SSD2825_Initial
		W_C(0xb7);
		W_D(0x50);
		W_D(0x00);	 //Configuration Register
	
		W_C(0xb8);
		W_D(0x00);
		W_D(0x00);	 //VC(Virtual ChannelID) Control Register
	
		W_C(0xb9);
		W_D(0x00);//1=PLL disable
		W_D(0x00);
	
		W_C(0xBA);//PLL=(TX_CLK/MS)*NS 8228=480M 4428=240M	061E=120M 4214=240M 821E=360M 8219=300M 8225=444M 8224=432
		W_D(0x38);//D7-0=NS(0x01 : NS=1)  //27
		W_D(0x82);//D15-14=PLL·¶Î§ 00=62.5-125 01=126-250 10=251-500 11=501-1000  DB12-8=MS(01:MS=1)  //82
	
		W_C(0xBB);//LP Clock Divider LP clock = 400MHz / LPD / 8 = 480 / 8/ 8 = 7MHz
		W_D(0x07);//D5-0=LPD=0x1 \u0161C Divide by 2
		W_D(0x00);
	
		W_C(0xb9);
		W_D(0x01);//1=PLL disable
		W_D(0x00);
	
		W_C(0xc9);
		W_D(0x02);
		W_D(0x23);	 //p1: HS-Data-zero  p2: HS-Data- prepare  --> 8031 issue
		mdelay(100);
	
		W_C(0xCA);
		W_D(0x01);//CLK Prepare
		W_D(0x23);//Clk Zero
	
		W_C(0xCB); //local_write_reg(addr=0xCB,data=0x0510)
		W_D(0x10); //Clk Post
		W_D(0x05); //Clk Per
	
		W_C(0xCC); //local_write_reg(addr=0xCC,data=0x100A)
		W_D(0x05); //HS Trail
		W_D(0x10); //Clk Trail
	
		W_C(0xD0);
		W_D(0x00);
		W_D(0x00);
	
		//RGB interface configuration
		W_C(0xB1);
		W_D(HSPW);//HSPW 07
		W_D(VSPW);//VSPW 05
	
		W_C(0xB2);
		W_D(HBPD);//HBPD 0x64=100
		W_D(VBPD);//VBPD 8 \u0152õÐ¡ÏÂÒÆ
	
		W_C(0xB3);
		W_D(HFPD);//HFPD 8
		W_D(VFPD);//VFPD 10
	
	
		W_C(0xB4);//Horizontal active period 720=02D0
		W_D(0x20);//013F=319 02D0=720
		W_D(0x03);
	
		W_C(0xB5);//Vertical active period 1280=0500
		W_D(0x20);//01DF=479 0500=1280
		W_D(0x03);
	
		
		W_C(0xB6);//RGB CLK  16BPP=00 18BPP=01
		W_D(0x04);//D7=0 D6=0 D5=0	D1-0=11 \u0161C 24bpp
		W_D(0x20);//D15=VS D14=HS D13=CLK D12-9=NC D8=0=Video with blanking packet. 00-F0
	
	
		//MIPI lane configuration
		W_C(0xDE);//Í\u0161µÀÊý
		W_D(0x02);//11=4LANE 10=3LANE 01=2LANE 00=1LANE
		W_D(0x00);
	
		W_C(0xD6);//  05=BGR  04=RGB
		W_D(0x04);//D0=0=RGB 1:BGR D1=1=Most significant byte sent first
		W_D(0x00);
	
	
		W_C(0xB7);
		W_D(0x2B);	//4B
		W_D(0x02);
	
		W_C(0x2C);
	

	
    return 0;
}


int ILI9881C_standby(void)
{
    return 0;
}

