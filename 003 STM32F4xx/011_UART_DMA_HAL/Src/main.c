#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "clock.h"
#include "uart.h"
#include "itm.h"

int main (void)
{
	HAL_Init(); 			// Initialize HAL and SysTick
	SystemClock_Config(); 	// Configure System Clocks
	ITM_Init();				// ITM Module Initialization
	UART_DMA_Init(); 		// Initialize UART

	printf("UART RX-TX Configured with DMA...\n");

	while (1)
	{

	}
}

void SysTick_Handler (void)
{
	HAL_IncTick();
}
