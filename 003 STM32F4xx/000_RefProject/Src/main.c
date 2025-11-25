#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "clock.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks

	while (1)
	{

	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
