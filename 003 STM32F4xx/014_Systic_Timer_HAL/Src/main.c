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
		HAL_Delay(1000);
		printf("1 Second Elapsed\n");
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
