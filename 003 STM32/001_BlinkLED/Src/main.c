#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "clock.h"
#include "gpio.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	GPIO_Init();                // Initialize PD12 as output

	while (1)
	{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12); // Toggle PD12
		HAL_Delay(500);                         // 500 ms delay
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
