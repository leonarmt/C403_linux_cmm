#ifndef __SSD2828_H__
#define __SSD2828_H__


void ssd2828_gpio_init(void);
void ssd2828_reset(void);
void W_C(int data);
void W_D(int data);

void GP_COMMAD_PA(int a);


void SPI_READ_ID(void);

#endif


