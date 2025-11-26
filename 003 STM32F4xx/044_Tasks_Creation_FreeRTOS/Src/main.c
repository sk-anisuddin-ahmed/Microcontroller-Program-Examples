#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "FreeRTOS.h"
#include "task.h"

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    taskDISABLE_INTERRUPTS();
    while(1);
}

void Task1(void *pvParameters)
{
	while (1)
	{
		printf("Hello from Task1\n");
		vTaskDelay(2500);
	}
}

void Task2(void *pvParameters)
{
    while (1)
    {
    	vTaskDelay(2500);
    	printf("Hello from Task2\n");
    }
}

int main(void)
{
	HAL_Init();                 // Initialize HAL and SysTick
	SystemClock_Config();       // Configure system clocks
	ITM_Init();

	xTaskCreate(Task1, "Task1", 128, NULL, 1, NULL);
	xTaskCreate(Task2, "Task2", 256, NULL, 1, NULL);
	vTaskStartScheduler();

	while (1)
	{

	}
}
