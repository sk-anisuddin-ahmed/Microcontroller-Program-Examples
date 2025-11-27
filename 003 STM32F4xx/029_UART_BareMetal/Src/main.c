#include <stdio.h>
#include <stdint.h>
#include "itm.h"
#include "sysTick.h"
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"
#include "uart.h"

int main(void)
{
	SysTick_Init();
	UART2_Init();

    while(1)
    {
    	printf("Hello India\n");
    	msDelay(1000);
    }
}
