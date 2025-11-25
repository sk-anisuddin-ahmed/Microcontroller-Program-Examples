/*
 * delay.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include "stm32f4xx_hal.h"

void DWT_Init(void)
{
    // Enable TRC
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // Reset the cycle counter
    DWT->CYCCNT = 0;
    // Enable the cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t elapsedMicroseconds(void)
{
    // Wait for Echo pin to go HIGH
    while (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == GPIO_PIN_RESET)
    {

    }

    // Reset the cycle counter
	DWT->CYCCNT = 0;

    // Wait for Echo pin to go LOW
    while (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == GPIO_PIN_SET)
    {
    	if (DWT->CYCCNT > (HAL_RCC_GetSysClockFreq() / 1000))
    		return 0;
    }

    uint32_t time = DWT->CYCCNT;

    // Convert cycles to microseconds
    uint32_t cycles_per_us = HAL_RCC_GetSysClockFreq() / 1000000;
    return (uint32_t)(time / cycles_per_us);
}

void delayMicroseconds(uint32_t us)
{
	// Reset the cycle counter
	DWT->CYCCNT = 0;

    uint32_t cycles_per_us = HAL_RCC_GetSysClockFreq() / 1000000;
    uint32_t target = us * cycles_per_us;

    while ((DWT->CYCCNT) < target);
}
