#include <stdio.h>

#include "stm32f4xx_hal.h"
#include "i2c.h"

I2C_HandleTypeDef hi2c1;

uint8_t rxData[7];
uint8_t reg = 0x00;

void I2C1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Enable clocks
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    // PB6 = SCL, PB7 = SDA
    GPIO_InitStruct.Pin       = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;       // Open-drain
    GPIO_InitStruct.Pull      = GPIO_PULLUP;           // Pull-up required
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configure I2C peripheral
    hi2c1.Instance             = I2C1;
    hi2c1.Init.ClockSpeed      = 100000;
    hi2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1     = 0;                    // Master mode
    hi2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2     = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c1);

    // Enable I2C interrupts in NVIC
	HAL_NVIC_SetPriority(I2C1_EV_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

	HAL_NVIC_SetPriority(I2C1_ER_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        HAL_I2C_Master_Receive_IT(&hi2c1, 0x68 << 1, rxData, 7);
    }
}

uint8_t bcd2dec(uint8_t val)
{
    return ((val >> 4) * 10) + (val & 0x0F);
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
    	printf("%02d:%02d\n",
    	       bcd2dec(rxData[2]), // hours
    	       bcd2dec(rxData[1]) // minutes
    	);
    }
}

void I2C1_EV_IRQHandler(void)
{
    HAL_I2C_EV_IRQHandler(&hi2c1);
}

void I2C1_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(&hi2c1);
}
