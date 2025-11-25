#include "stm32f4xx_hal.h"
#include "clock.h"
#include "itm.h"
#include "i2c.h"
#include <stdio.h>

uint8_t setTime[8] =
{
    0x00,   // start register address
    0x07,   // seconds (BCD)
    0x0D,   // minutes (BCD)
    0x12,   // hours (BCD, 24h mode)
    0x02,   // day of week (Tuesday)
    0x25,   // date (25th)
    0x11,   // month (November)
    0x25    // year (25 → 2025)
};

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    ITM_Init();
    I2C1_Init();

    //Set RTC Time
    HAL_I2C_Master_Transmit_IT(&hi2c1, 0x68 << 1, setTime, 8);

    while (1)
    {
    	HAL_Delay(1000);
    	HAL_I2C_Master_Transmit_IT(&hi2c1, 0x68 << 1, &reg, 1);
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
