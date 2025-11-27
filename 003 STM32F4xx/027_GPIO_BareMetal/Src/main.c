#include <stdio.h>
#include <stdint.h>
#include "itm.h"
#include "sysTick.h"
#include <rcc.h>
#include <gpio.h>

int main(void)
{
	SysTick_Init();
	ITM_Init();
	GPIO_Init();

    while(1)
    {
    	GPIOD.ODR.PIN12 ^= 1;
    	GPIOD.ODR.PIN13 ^= 1;
    	GPIOD.ODR.PIN14 ^= 1;
    	GPIOD.ODR.PIN15 ^= 1;
    	msDelay(1000);
    }
}
