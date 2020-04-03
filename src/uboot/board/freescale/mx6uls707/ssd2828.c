#include "ssd2828.h"

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

#define CS_OUT()        				 
#define CS_SET()        				gpio_direction_output(IMX_GPIO_NR(3, 26) , 1)
#define CS_CLR()        				gpio_direction_output(IMX_GPIO_NR(3, 26) , 0)

#define CLK_OUT()      					 
#define CLK_SET()       				gpio_direction_output(IMX_GPIO_NR(3, 25) , 1)
#define CLK_CLR()       				gpio_direction_output(IMX_GPIO_NR(3, 25) , 0)

#define TXD_OUT()       				 
#define TXD_SET()       				gpio_direction_output(IMX_GPIO_NR(3, 27) , 1)
#define TXD_CLR()       				gpio_direction_output(IMX_GPIO_NR(3, 27) , 0)

#define RXD_INPUT()						gpio_direction_input(IMX_GPIO_NR(3, 28))
#define RXD_GET()  						gpio_get_value(IMX_GPIO_NR(3, 28))


#define LCD_CS_CLR   CS_CLR()  
#define LCD_CS_SET   CS_SET()
#define LCD_SCL_SET  CLK_SET()
#define LCD_SCL_CLR  CLK_CLR()
#define LCD_SDA_SET  TXD_SET()
#define LCD_SDA_CLR  TXD_CLR()


static iomux_v3_cfg_t const ssd2828_pads[] = {

	MX6_PAD_LCD_DATA16__GPIO3_IO21 | MUX_PAD_CTRL(NO_PAD_CTRL),	/*ctp int*/
	MX6_PAD_LCD_DATA17__GPIO3_IO22 | MUX_PAD_CTRL(NO_PAD_CTRL),	/*ctp reset*/

	MX6_PAD_LCD_DATA18__GPIO3_IO23 | MUX_PAD_CTRL(NO_PAD_CTRL), /*lcd reset*/
	MX6_PAD_LCD_DATA19__GPIO3_IO24 | MUX_PAD_CTRL(NO_PAD_CTRL), /*lcd te*/
	MX6_PAD_LCD_DATA20__GPIO3_IO25 | MUX_PAD_CTRL(NO_PAD_CTRL), /*SPI SCK*/
	MX6_PAD_LCD_DATA21__GPIO3_IO26 | MUX_PAD_CTRL(NO_PAD_CTRL),	/*SPI CSB*/
	MX6_PAD_LCD_DATA22__GPIO3_IO27 | MUX_PAD_CTRL(NO_PAD_CTRL),	/*SPI MOSI*/
	MX6_PAD_LCD_DATA23__GPIO3_IO28 | MUX_PAD_CTRL(NO_PAD_CTRL),	/*SPI MISO*/
	
	MX6_PAD_GPIO1_IO00__GPIO1_IO00 | MUX_PAD_CTRL(NO_PAD_CTRL),	/*ssd2828 reset*/
	MX6_PAD_GPIO1_IO01__GPIO1_IO01 | MUX_PAD_CTRL(NO_PAD_CTRL),	/*ssd2828 shut*/
};

void ssd2828_gpio_init(void)
{
	imx_iomux_v3_setup_multiple_pads(ssd2828_pads, ARRAY_SIZE(ssd2828_pads));
	RXD_INPUT();
	CS_OUT();
	CLK_OUT();
	TXD_OUT();
}

void ssd2828_reset(void)
{
	gpio_direction_output(IMX_GPIO_NR(1, 1) , 0);	 //shut

	gpio_direction_output(IMX_GPIO_NR(3, 23) , 1);	//lcd reset 
	mdelay(100);
	
	gpio_direction_input(IMX_GPIO_NR(3, 24));		//lcd te input
	gpio_direction_output(IMX_GPIO_NR(1, 0) , 0); 	//ssd2828 reset
	gpio_direction_output(IMX_GPIO_NR(3, 23) , 0);	//lcd reset 
	mdelay(100);
	gpio_direction_output(IMX_GPIO_NR(1, 0) , 1);
	gpio_direction_output(IMX_GPIO_NR(3, 23) , 1);
	mdelay(200);	
}

void spi_delay(void)
{
	udelay(1); 
}

 void W_C(int data)
 {
 // RS=0
	int i;
	LCD_CS_CLR;
	spi_delay();
	LCD_SDA_CLR;
	spi_delay();
	LCD_SCL_CLR;
	spi_delay();
	LCD_SCL_SET;
	spi_delay();
 
	for(i=0;i<8;i++)
	{
	   if (data & 0x80)
	   {
	   	LCD_SDA_SET;
	   	spi_delay();
	   }
	   else
	   {
	    LCD_SDA_CLR;
		spi_delay();
	   }
 
	    data<<= 1;
	    LCD_SCL_CLR;
	    spi_delay();
	    LCD_SCL_SET;
  	    spi_delay();
 
	 }
    LCD_CS_SET;
    spi_delay();
 }
 
 void W_D(int data)
 {
 //RS=1
	int i;
	LCD_CS_CLR;
	spi_delay();
    LCD_SDA_SET;//BIT8=0 COMM
    spi_delay();
	LCD_SCL_CLR;
    spi_delay();
	LCD_SCL_SET;
	spi_delay();
 
	for(i=0;i<8;i++)
	{
 
	if (data & 0x80)
	   {LCD_SDA_SET;spi_delay();}
	else
	   {LCD_SDA_CLR;spi_delay();}
 
	 data<<= 1;
	 LCD_SCL_CLR;
     spi_delay();
	 LCD_SCL_SET;
	 spi_delay();
 
	}
 	LCD_CS_SET;
 	spi_delay();
	
  }
  
 void writed16(int data)
 {
 //RS=1
	int i;
 
	LCD_CS_CLR;
    spi_delay();
    LCD_SDA_SET;//BIT8=0 COMM
    spi_delay();
	LCD_SCL_CLR;
    spi_delay();
	LCD_SCL_SET;
	spi_delay();
 
	for(i=0;i<8;i++)
	{
 
		if (data & 0x80)
		{
	   	   LCD_SDA_SET;
	   	   spi_delay();
		}
	    else
	    {
	       LCD_SDA_CLR;
	       spi_delay();
	    }
 
		 data<<= 1;
		 LCD_SCL_CLR;
   		 spi_delay();
	 	 LCD_SCL_SET;
  	 	 spi_delay();
	 }
	
 	LCD_CS_SET;
 	spi_delay();
 }

 void GP_COMMAD_PA(int a)
{
 	W_C(0xBC);
	writed16(a);
	writed16(a>>8);
	W_C(0xBF);
}

short  SPI_READ(void)
{
	char  cmd,rdT;
	short reValue;
	int kk;
	
	LCD_CS_CLR;

	LCD_SDA_CLR;			//Set DC=0, for writing to Command register
	LCD_SCL_CLR;
	LCD_SCL_SET;
	

	cmd = 0xB0;
	LCD_SCL_CLR;
	for(kk=0;kk<8;kk++)
	{
		if((cmd&0x80)==0x80) 
			LCD_SDA_SET;
		else
			LCD_SDA_CLR;
		LCD_SCL_SET;
		LCD_SCL_CLR;
		cmd = cmd<<1;	 
	}
	
	LCD_SDA_CLR;		//Set DC=0, for writing to Command register
	LCD_SCL_CLR;
	LCD_SCL_SET;
	

	cmd = 0xFA;
	LCD_SCL_CLR;
	for(kk=0;kk<8;kk++)
	{
		if((cmd&0x80)==0x80)
			LCD_SDA_SET;
		else
			LCD_SDA_CLR;
		LCD_SCL_SET;
		LCD_SCL_CLR;
		cmd = cmd<<1;	
	}	
	
	rdT=0;
	for(kk=0;kk<8;kk++)
	{
		rdT = rdT<<1;
		LCD_SCL_SET;
		//if((gpio->rGPBDAT)&0x0400) rdT |= 0x01;
			if(RXD_GET())
		rdT |= 0x01;
			
		LCD_SCL_CLR;			
	}
	
	reValue = rdT;
	//reValue = (reValue<<8)&0xFF00;
	
	rdT=0;
	for(kk=0;kk<8;kk++)
	{
		rdT = rdT<<1;
		LCD_SCL_SET;
		//if((gpio->rGPBDAT)&0x0400) 
		if(RXD_GET())
		rdT |= 0x01;

		LCD_SCL_CLR;			
	}
	
	reValue += (rdT<<8);
	
	LCD_CS_SET;
	
	return reValue;			
}

void Wr_com_data16(char c,short value)
{
	LCD_CS_CLR;
	W_C(c);
	W_D(value&0xff);
	W_D((value>>8)&0xff);	
	LCD_CS_SET;	
}

void   SPI_READ_ID(void)
{
    int a;
	Wr_com_data16(0xd4, 0x00FA);
	a=SPI_READ();
	if(a==0x2828)
	{
		printf(" \n");
		printf("The SSD2828 ID: 0x%x  ^-^  successful !! \n",a);
		printf(" \n");
	}
	else
	{
		printf(" \n");
		printf("The SSD2828 ID: 0x%x  -_-! failing !!!! \n",a);
		printf(" \n");
	}
}


 


