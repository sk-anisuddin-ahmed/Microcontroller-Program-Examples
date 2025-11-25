#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "gpio.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	ITM_Init();
	GPIO_Init();

	int btnCnt = 0;

	while (1)
	{
	    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
	    {
	        HAL_Delay(200);
	        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
	        {
	            printf("Button Pressed: %d\n", ++btnCnt);
	            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
	        }
	    }
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
