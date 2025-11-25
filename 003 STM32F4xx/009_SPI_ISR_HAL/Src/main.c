#include "stm32f4xx_hal.h"
#include "clock.h"
#include "spi.h"
#include "itm.h"
#include <stdio.h>

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    ITM_Init();
    SPI1_Init();

    while (1)
    {

    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
