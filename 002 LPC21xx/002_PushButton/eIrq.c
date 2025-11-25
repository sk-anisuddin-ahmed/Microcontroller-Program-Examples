#include <LPC213x.h>
#include <stdint.h>

void LED_UPDATE(int);
uint8_t buttonCount;

void __irq EINT0_ISR(void) 
{
		LED_UPDATE(++buttonCount);
    EXTINT = (1 << 0);      // clear EINT0 flag	
    VICVectAddr = 0x00;     // acknowledge VIC
}

void EINT(void)
{
		PINSEL1 &= ~0x03;   // clear bits 1:0
		PINSEL1 |= 0x01;    // set to 01 - EINT0
		EXTMODE  |= (1 << 0);   // EINT0 edge sensitive
		EXTPOLAR &= ~(1 << 0);  // falling edge

    VICIntSelect &= ~(1 << 14);
    VICVectAddr2 = (unsigned long)EINT0_ISR;
    VICVectCntl2 = (1 << 5) | 14;
    VICIntEnable = (1 << 14);
}
