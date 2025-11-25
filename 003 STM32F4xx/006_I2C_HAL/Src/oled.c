/*
 * oled.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include "stm32f4xx_hal.h"
#include "i2c.h"

#define OLED_ADDR 0x3C << 1

void OLED_SendCommand(uint8_t cmd)
{
    uint8_t buffer[2];
    buffer[0] = 0x00;
    buffer[1] = cmd;
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buffer, 2, HAL_MAX_DELAY);
}

void OLED_SendData(uint8_t data)
{
    uint8_t buffer[2];
    buffer[0] = 0x40;
    buffer[1] = data;
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buffer, 2, HAL_MAX_DELAY);
}

void OLED_Clear(void)
{
    for (uint16_t i = 0; i < 1024; i++)
    {
        OLED_SendData(0x00);
    }
}

void OLED_Fill(void)
{
    for (uint16_t i = 0; i < 1024; i++)
    {
        OLED_SendData(0xFF);
    }
}

void OLED_SetCursor(uint8_t col, uint8_t page)
{
    OLED_SendCommand(0x21); // Set column address
    OLED_SendCommand(col);
    OLED_SendCommand(127);
    OLED_SendCommand(0x22); // Set page address
    OLED_SendCommand(page);
    OLED_SendCommand(7);
}

void OLED_DrawHLine(uint8_t x1, uint8_t x2, uint8_t y)
{
    uint8_t page = y / 8;
    uint8_t bit = y % 8;
    uint8_t data = (1 << bit);

    for (uint8_t x = x1; x <= x2; x++)
    {
        OLED_SetCursor(x, page);
        OLED_SendData(data);
    }
}

void OLED_DrawVLine(uint8_t x, uint8_t y1, uint8_t y2)
{
    uint8_t page_start = y1 / 8;
    uint8_t page_end   = y2 / 8;

    for (uint8_t page = page_start; page <= page_end; page++)
    {
        OLED_SetCursor(x, page);
        OLED_SendData(0xFF);
    }
}

void OLED_DrawBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    OLED_DrawHLine(x1, x2, y1);
    OLED_DrawHLine(x1, x2, y2);
    OLED_DrawVLine(x1, y1, y2);
    OLED_DrawVLine(x2, y1, y2);
}

void OLED_Init(void)
{
    HAL_Delay(100);

    OLED_SendCommand(0xAE); // Display OFF
    OLED_SendCommand(0x20); // Set Memory Addressing Mode
    OLED_SendCommand(0x00); // Horizontal addressing mode
    OLED_SendCommand(0x8D); // Charge Pump
    OLED_SendCommand(0x14); // Enable charge pump
    OLED_SendCommand(0xA6); // Normal display (not inverted)
    OLED_SendCommand(0xAF); // Display ON

    OLED_Clear();
    OLED_DrawBox(27, 14, 100, 50);
}
