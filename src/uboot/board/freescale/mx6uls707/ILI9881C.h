#ifndef __ILI9881C_H__
#define __ILI9881C_H__

#define	VBPD  30
#define	VFPD  10
#define	VSPW  4

#define	HBPD  30
#define	HFPD  10 
#define	HSPW  10

int ILI9881C_init(void);
int ILI9881C_standby(void);

#endif

