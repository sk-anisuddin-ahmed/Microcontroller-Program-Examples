#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "rtc.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	ITM_Init();
	RTC_INIT();

	while (1)
	{
		HAL_Delay(1000);
		RTC_Read();
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
