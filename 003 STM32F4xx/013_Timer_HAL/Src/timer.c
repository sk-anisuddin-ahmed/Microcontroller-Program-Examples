/*
 * timer.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "timer.h"

TIM_HandleTypeDef TimHandle;

void TIM3_Init(void)
{
    /* Enable TIM3 clock */
    __HAL_RCC_TIM3_CLK_ENABLE();

    TimHandle.Instance = TIM3;
    TimHandle.Init.Prescaler = 8400 - 1;
    TimHandle.Init.Period    = 10000 - 1;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_Base_Init(&TimHandle);

    /* Enable interrupt in NVIC */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    /* Start timer in interrupt mode */
    HAL_TIM_Base_Start_IT(&TimHandle);
}

/* IRQ handler for TIM3 */
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TimHandle);
}

/* HAL callback: runs every time the period elapses */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        printf("1 Second Elapsed!\n");
    }
}
