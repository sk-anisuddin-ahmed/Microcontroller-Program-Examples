#include "stm32f4xx_hal.h"
#include "clock.h"
#include "itm.h"
#include "i2c.h"
#include "oled.h"
#include <stdio.h>

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    ITM_Init();
    I2C1_Init();
    OLED_Init();

    while (1)
    {

    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
