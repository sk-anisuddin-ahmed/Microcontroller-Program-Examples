#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "itm.h"
#include "clock.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Queue handle */
QueueHandle_t xQueue;

/* Producer Task */
void vProducerTask(void *pvParameters)
{
    int value = 0;
    while (1)
    {
        value++;
        if (xQueueSend(xQueue, &value, portMAX_DELAY) == pdPASS)
        {
            printf("Sent: %d\n", value);
        }
        vTaskDelay(pdMS_TO_TICKS(500)); // Produce every 500 ms
    }
}

/* Consumer Task */
void vConsumerTask(void *pvParameters)
{
    int receivedValue;
    while (1)
    {
        if (xQueueReceive(xQueue, &receivedValue, portMAX_DELAY) == pdPASS)
        {
            printf("Received: %d\n", receivedValue);
        }
    }
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    /* Create a queue c - 10 integers */
	xQueue = xQueueCreate(10, sizeof(int));
	/* Create tasks */
	xTaskCreate(vProducerTask, "Producer", 128, NULL, 1, NULL);
	xTaskCreate(vConsumerTask, "Consumer", 128, NULL, 1, NULL);

	/* Start scheduler */
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
