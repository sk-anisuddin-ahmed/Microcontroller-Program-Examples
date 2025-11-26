#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "queue.h"

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    taskDISABLE_INTERRUPTS();
    while(1);
}

SemaphoreHandle_t xPrintMutex;

void vUartTask(void *pvParameters)
{
    while(1)
    {
		if (xSemaphoreTake(xPrintMutex, portMAX_DELAY) == pdTRUE)
		{
			printf("Hello from %s\n", pcTaskGetName(NULL));
			xSemaphoreGive(xPrintMutex);
		}
		vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	ITM_Init();

	xPrintMutex = xSemaphoreCreateMutex();

	xTaskCreate(vUartTask, "Task1", 128, NULL, 1, NULL);
	xTaskCreate(vUartTask, "Task2", 128, NULL, 1, NULL);

	vTaskStartScheduler();

    while(1)
    {

    }
}
