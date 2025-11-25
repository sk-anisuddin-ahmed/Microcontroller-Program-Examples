/*
 * gpio.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include "stm32f4xx_hal.h"

void GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();   // Enable clock for GPIOD

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   = GPIO_PIN_12;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; // Push-pull output
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
