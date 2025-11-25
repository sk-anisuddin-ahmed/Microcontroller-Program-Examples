#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "clock.h"
#include "uart.h"

int main(void)
{
    HAL_Init();                 // Initialize HAL and SysTick
    SystemClock_Config();       // Configure system clocks
    UART_Init();                // Initialize UART

    while (1)
    {
        if (rxIndex >= 5)
		{
			rxBuf[rxIndex] = '\0';
			printf("Received buffer: %s\r\n", rxBuf);
			rxIndex = 0;
		}
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
