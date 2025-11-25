#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "gpio.h"
#include "delay.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	ITM_Init();
	GPIO_Init();

	uint32_t echoTimeus = 0;

	while (1)
	{
	    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
	    {
	        HAL_Delay(200);
	        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
	        {
	        	printf("Trigger Send\n");
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
				delayMicroseconds(10);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
				delayMicroseconds(2);

	            echoTimeus = elapsedMicroseconds();
	            printf("Echo Time in us: %lu\n", echoTimeus);
	            // Convert to distance
				float distance_cm = (echoTimeus * 0.0343f) / 2.0f;
				printf("Distance: %.2f cm\n", distance_cm);
	        }
	        while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET);
	    }
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
