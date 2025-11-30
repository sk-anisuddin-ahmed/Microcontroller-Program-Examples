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

    }
}
