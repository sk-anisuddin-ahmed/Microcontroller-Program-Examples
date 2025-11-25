/*
 * gpio.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include "stm32f4xx_hal.h"

uint32_t btnCnt;
uint32_t lastPress;

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);   // Clear interrupt flag
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0)
    {
        uint32_t now = HAL_GetTick();

        if ((now - lastPress) > 200)
        {
            btnCnt++;
            printf("Button Pressed: %ld\n", btnCnt);
            lastPress = now;
        }
    }
}

void GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_SYSCFG_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // PA0 -> INPUT (User Button)
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;   // Falling edge (button press)
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Enable EXTI line 0 interrupt
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
