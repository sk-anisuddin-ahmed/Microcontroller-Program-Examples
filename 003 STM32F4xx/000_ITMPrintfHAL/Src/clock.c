/*
 * clock.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */


#include "stm32f4xx_hal.h"

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // 1) Enable HSI and configure PLL
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM       = 16;   // divide HSI 16 MHz / 16 = 1 MHz
    RCC_OscInitStruct.PLL.PLLN       = 336;  // multiply 1 MHz × 336 = 336 MHz
    RCC_OscInitStruct.PLL.PLLP       = RCC_PLLP_DIV4; // 336 / 4 = 84 MHz SYSCLK
    RCC_OscInitStruct.PLL.PLLQ       = 7;    // for USB clock (48 MHz)

    while (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK);

    // 2) Configure bus clocks
    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |
                                       RCC_CLOCKTYPE_PCLK1  | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;   // HCLK = 84 MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;     // PCLK1 = 42 MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;     // PCLK2 = 84 MHz

    while (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK);

    SystemCoreClockUpdate();
}
