#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "FreeRTOS.h"
#include "task.h"

volatile int ledOn = 0;   // Shared flag

/* LED Init (PD13) */
static void LED_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/* Button Init (PA0) */
static void Button_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;   // Blue button has external pull-down
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* Task1: LED control */
void Task1(void *pvParameters)
{
	while (1)
    {
        if (ledOn)
        {
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
            vTaskDelay(pdMS_TO_TICKS(500));  // blink every 500 ms
        }
        else
        {
            HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
            vTaskDelay(pdMS_TO_TICKS(100));  // small wait
        }
    }
}

/* Task2: Button monitor*/
TaskHandle_t xButtonTaskHandle;
void Task2(void *pvParameters)
{
    while (1)
    {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        {
        	ledOn = 1;
            vTaskDelete(NULL);
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // poll every 50 ms
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    ITM_Init();
    LED_Init();
    Button_Init();

    xTaskCreate(Task1, "LED_Task", 128, NULL, 1, NULL);
    xTaskCreate(Task2, "Button_Task", 128, NULL, 1, &xButtonTaskHandle);

    printf("FreeRTOS Scheduler is Enabled\n");

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
