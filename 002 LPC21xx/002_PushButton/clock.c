#include <LPC213x.h>
#include "clock.h"

void CLOCK_INIT(void) 
{
    /*Configure Memory Accelerator Module (MAM) */
    MAMCR  = 0x02;   // Enable MAM
    MAMTIM = 0x04;   // 4 cycles

    /*Enable PLL*/
    PLLCON = 0x01;   // PLL enable
    PLLCFG = (5 - 1) | (1 << 5);   // M=5, P=2
    PLLFEED = 0xAA;  // Feed sequence
    PLLFEED = 0x55;

    /*Wait for PLL to lock */
    while (!(PLLSTAT & (1 << 10)));  // PLOCK bit

    /*Connect PLL */
    PLLCON = 0x03;   // Enable + Connect
    PLLFEED = 0xAA;
    PLLFEED = 0x55;

    /*Set VPBDIV - Peripheral Clock*/
    VPBDIV = 0x01;   // PCLK = CCLK = 60 MHz
		PCONP = 0xFFFFFFFF;
}