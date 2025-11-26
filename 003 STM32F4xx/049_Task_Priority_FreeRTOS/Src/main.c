#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "FreeRTOS.h"
#include "task.h"

/* LED (PD12 green, PD13 orange) */
static void LED_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Task1(void *pvParameters)
{
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
    }
}

void Task2(void *pvParameters)
{
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    LED_Init();

    xTaskCreate(Task1, "Low", 128, NULL, 2, NULL);
    xTaskCreate(Task2, "High", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1)
    {

    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    taskDISABLE_INTERRUPTS();
    while(1);
}
