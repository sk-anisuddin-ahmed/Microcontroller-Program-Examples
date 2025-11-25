#include <LPC213x.h>
#include "gpio.h"

void KEYPAD_INIT(void) 
{
    // Rows as output
    IO0DIR |= (ROWA | ROWB | ROWC | ROWD);
}

void GPIO_INIT(void)
{
    //All pins set to GPIO
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;

    //All pins as input
    IO0DIR = 0x00000000;
    IO1DIR = 0x00000000;
	
		KEYPAD_INIT();
}
