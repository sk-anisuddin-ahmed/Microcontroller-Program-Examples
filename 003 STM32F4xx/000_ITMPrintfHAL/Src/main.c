#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	ITM_Init();

	while (1)
	{
		printf("Hello World\n");
		HAL_Delay (1000);
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
