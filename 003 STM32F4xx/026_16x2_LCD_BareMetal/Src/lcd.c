/*
 * File:   lcd.c
 * Author: Sk.Anisuddin
 *
 * Created on 28 July, 2023, 4:44 PM
 */

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "lcd.h"
#include "rcc.h"
#include "sysTick.h"

void LCD_PIN_INIT(void)
{
	// Enable GPIOD clock
	RCC.AHB1ENR.GPIODEN = RCC_ENABLE;

	// RS -> PD0
	GPIOD.MODER.PIN0 = GPIO_MODE_OUTPUT;
	GPIOD.OTYPER.PIN0 = GPIO_OTYPE_PP;
	GPIOD.OSPEEDR.PIN0 = GPIO_SPEED_HIGH;
	GPIOD.PUPDR.PIN0 = GPIO_NOPULL;

	// EN -> PD1
	GPIOD.MODER.PIN1 = GPIO_MODE_OUTPUT;
	GPIOD.OTYPER.PIN1 = GPIO_OTYPE_PP;
	GPIOD.OSPEEDR.PIN1 = GPIO_SPEED_HIGH;
	GPIOD.PUPDR.PIN1 = GPIO_NOPULL;

	// D4 -> PD9
	GPIOD.MODER.PIN9 = GPIO_MODE_OUTPUT;
	GPIOD.OTYPER.PIN9 = GPIO_OTYPE_PP;
	GPIOD.OSPEEDR.PIN9 = GPIO_SPEED_HIGH;
	GPIOD.PUPDR.PIN9 = GPIO_NOPULL;

	// D5 -> PD10
	GPIOD.MODER.PIN10 = GPIO_MODE_OUTPUT;
	GPIOD.OTYPER.PIN10 = GPIO_OTYPE_PP;
	GPIOD.OSPEEDR.PIN10 = GPIO_SPEED_HIGH;
	GPIOD.PUPDR.PIN10 = GPIO_NOPULL;

	// D6 -> PD11
	GPIOD.MODER.PIN11 = GPIO_MODE_OUTPUT;
	GPIOD.OTYPER.PIN11 = GPIO_OTYPE_PP;
	GPIOD.OSPEEDR.PIN11 = GPIO_SPEED_HIGH;
	GPIOD.PUPDR.PIN11 = GPIO_NOPULL;

	// D7 -> PD8
	GPIOD.MODER.PIN8 = GPIO_MODE_OUTPUT;
	GPIOD.OTYPER.PIN8 = GPIO_OTYPE_PP;
	GPIOD.OSPEEDR.PIN8 = GPIO_SPEED_HIGH;
	GPIOD.PUPDR.PIN8 = GPIO_NOPULL;
}

void LCD_BEGIN()
{
    LCD_PIN_INIT();
    msDelay(15);
    LCD_COMMAND(0x02);
    LCD_COMMAND(0x28);
    LCD_COMMAND(0x0C);
    LCD_COMMAND(0x01);
    LCD_COMMAND(0x06);
    LCD_COMMAND(0x80);
}

void LCD_CLEAR(void)
{
    LCD_COMMAND(0x01);
}

// Send 4 bits to LCD
void LCD_WRITE_NIBBLE(uint8_t value)
{
    D4 = (value >> 0) & 0x01;
    D5 = (value >> 1) & 0x01;
    D6 = (value >> 2) & 0x01;
    D7 = (value >> 3) & 0x01;

    LCD_ENABLE_PULSE();
}

_Bool LCD_WRITE_ONGOING = false;

// Send 8 bits to LCD
void LCD_WRITE_CHAR(uint8_t value)
{
    LCD_WRITE_ONGOING = true;

    D7 = (value >> 7) & 0x01;
    D6 = (value >> 6) & 0x01;
    D5 = (value >> 5) & 0x01;
    D4 = (value >> 4) & 0x01;

    LCD_ENABLE_PULSE();

    D7 = (value >> 3) & 0x01;
    D6 = (value >> 2) & 0x01;
    D5 = (value >> 1) & 0x01;
    D4 = (value >> 0) & 0x01;

    LCD_ENABLE_PULSE();

    LCD_WRITE_ONGOING = false;
}

void LCD_COMMAND(uint8_t value)
{
    RS = COMMAND;
    LCD_WRITE_CHAR(value);
}

void LCD_COMMAND_4BIT(uint8_t value)
{
    RS = COMMAND;
    LCD_WRITE_NIBBLE(value);
}

void LCD_WRITE_8BIT(uint8_t value)
{
    RS = DATA;
    LCD_WRITE_CHAR(value);
}

void LCD_SET_CURSOR(uint8_t col, uint8_t row)
{
    /*
     ************* Display Position ***************
    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
    -----------------------------------------------
    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
    40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F
     */
    static uint8_t row_offsets[] = {0x00, 0x40};
    LCD_COMMAND(0x80 | (col + row_offsets[row]));
}

void LCD_SEND_STRING(char* msg)
{
    uint8_t i = 0;
    while (msg[i] != '\0')
    {
        LCD_WRITE_8BIT((uint8_t) msg[i]);
        i++;
    }
}

void LCD_ENABLE_PULSE()
{
    EN = HIGH;
    msDelay(1);
    EN = LOW;
    msDelay(2); // Enable pulse must be > 37us to settle
}
