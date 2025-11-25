#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "adc.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	ITM_Init();
	ADC_INIT();

	while (1)
	{
		HAL_Delay(1000);
		HAL_ADC_Start_IT(&hadc1);
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
