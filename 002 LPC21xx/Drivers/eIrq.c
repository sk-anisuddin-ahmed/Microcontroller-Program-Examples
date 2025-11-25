#include <LPC213x.h>

void __irq EINT2_ISR(void) 
{    
	
    EXTINT = (1<<2);        // clear EINT2 flag
    VICVectAddr = 0x00;     // acknowledge VIC
}

void EINT(void)
{
    PINSEL1 |= (3<<0);      // P0.16 as EINT2
    EXTMODE  |= (1<<2);     // edge sensitive
    EXTPOLAR &= ~(1<<2);    // falling edge

    VICIntSelect &= ~(1<<16);
    VICVectAddr2 = (unsigned long)EINT2_ISR;
    VICVectCntl2 = (1<<5) | 16;
    VICIntEnable = (1<<16);
}
