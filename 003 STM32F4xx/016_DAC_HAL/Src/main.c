#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "adc.h"
#include "dac.h"

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	ITM_Init();
	ADC_INIT();
	DAC1_INIT();

	while (1)
	{
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2048); // ~1.65V
		printf("DAC Value: 2048\n");
		HAL_Delay(500);
		HAL_ADC_Start_IT(&hadc1);
		HAL_Delay(500);

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 4095); // ~3.3V
		printf("DAC Value: 4095\n");
		HAL_Delay(500);
		HAL_ADC_Start_IT(&hadc1);
		HAL_Delay(500);

		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);    // 0V
		printf("DAC Value: 0\n");
		HAL_Delay(500);
		HAL_ADC_Start_IT(&hadc1);
		HAL_Delay(500);
		printf("\n");
	}
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
