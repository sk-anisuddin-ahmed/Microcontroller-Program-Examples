#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "clock.h"
#include "itm.h"
#include "dma.h"

int main (void)
{
	HAL_Init(); 			// Initialize HAL and SysTick
	SystemClock_Config(); 	// Configure System Clocks
	ITM_Init();				// ITM Module Initialization
	DMA_INIT(); 			// Initialize DMA

	while (1)
	{

	}
}

void SysTick_Handler (void)
{
	HAL_IncTick();
}
