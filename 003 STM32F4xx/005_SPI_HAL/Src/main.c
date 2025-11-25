#include "stm32f4xx_hal.h"
#include "clock.h"
#include "spi.h"
#include "itm.h"
#include <stdio.h>

uint8_t txData[] = "Hello SPI";
uint8_t rxData[32];

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    ITM_Init();
    SPI1_Init();

    while (1)
    {
        // Transmit and receive simultaneously (full-duplex)
        if (HAL_SPI_TransmitReceive(&hspi1, txData, rxData, sizeof(txData), HAL_MAX_DELAY) == HAL_OK)
        {
            printf("SPI Tx: %s\r\n", txData);
            printf("SPI Rx: %s\r\n\n", rxData);
        }

        HAL_Delay(1000);
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
