#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "FreeRTOS.h"
#include "task.h"

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
TaskHandle_t xLedTaskHandle;
void Task1(void *pvParameters)
{
	while (1)
    {
		// Block until notified
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

		// Toggle LED when notified
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
    }
}

/* Task2: Button sends notification */
void Task2(void *pvParameters)
{
    while(1)
    {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        {
            // Notify LED task
            xTaskNotifyGive(xLedTaskHandle);

            vTaskDelay(pdMS_TO_TICKS(300)); // simple debounce
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    ITM_Init();
    LED_Init();
    Button_Init();

    xTaskCreate(Task1, "LED_Task", 128, NULL, 1, &xLedTaskHandle);
	xTaskCreate(Task2, "Button_Task", 128, NULL, 1, NULL);

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
