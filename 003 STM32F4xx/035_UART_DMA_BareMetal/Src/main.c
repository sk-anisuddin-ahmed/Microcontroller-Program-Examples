#include <stdio.h>
#include <stdint.h>
#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "uart.h"
#include "dma.h"

int main(void)
{
	SysTick_Init();
	UART2_DMA_Init();

    while(1)
    {
    	UART2_DMA_Send ((uint8_t*)"Hello World\n", 12);
    	msDelay(1000);
    }
}
