#include <LPC213x.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "lcd.h"
#include "timer.h"

void LCD_PIN_INIT(void)
{
    //LCD_D4
    IO1DIR |= ((unsigned long)1 << 20);
    //LCD_D5
    IO1DIR |= ((unsigned long)1 << 21);
    //LCD_D6
    IO1DIR |= ((unsigned long)1 << 22);
    //LCD_D7
    IO1DIR |= ((unsigned long)1 << 23);
    //LCD_RS
    IO0DIR |= ((unsigned long)1 << 29);
    //LCD_EN
    IO0DIR |= ((unsigned long)1 << 31);
}

void LCD_BEGIN()
{
    LCD_PIN_INIT();
    T1_delay_ms(15);
    LCD_COMMAND(0x02); // Return Home (set 4-bit mode)
		LCD_COMMAND(0x28); // Function Set: 4-bit, 2 lines, 5x8 dots
		LCD_COMMAND(0x0C); // Display ON, Cursor OFF
		LCD_COMMAND(0x01); // Clear Display
		LCD_COMMAND(0x06); // Entry Mode: Increment cursor
		LCD_COMMAND(0x80); // Set DDRAM address to 0x00 (home position)
}

void LCD_CLEAR(void)
{
    LCD_COMMAND(0x01);
}

// Send 4 bits to LCD
void LCD_WRITE_NIBBLE(uint8_t value)
{
		if ((value >> 0) & 0x01)
		{
				D4_HIGH;
		}
		else
		{
				D4_LOW;
		}
		
		if ((value >> 1) & 0x01)
		{
				D5_HIGH;
		}
		else
		{
				D5_LOW;
		}
		
		if ((value >> 2) & 0x01)
		{
				D6_HIGH;
		}
		else
		{
				D6_LOW;
		}
		
		if ((value >> 3) & 0x01)
		{
				D7_HIGH;
		}
		else
		{
				D7_LOW;
		}

    LCD_ENABLE_PULSE();
}

// Send 8 bits to LCD
void LCD_WRITE_CHAR(uint8_t value)
{
		if ((value >> 4) & 0x01)
		{
				D4_HIGH;
		}
		else
		{
				D4_LOW;
		}
		
		if ((value >> 5) & 0x01)
		{
				D5_HIGH;
		}
		else
		{
				D5_LOW;
		}
		
		if ((value >> 6) & 0x01)
		{
				D6_HIGH;
		}
		else
		{
				D6_LOW;
		}
		
		if ((value >> 7) & 0x01)
		{
				D7_HIGH;
		}
		else
		{
				D7_LOW;
		}

    LCD_ENABLE_PULSE();

    if ((value >> 0) & 0x01)
		{
				D4_HIGH;
		}
		else
		{
				D4_LOW;
		}
		
		if ((value >> 1) & 0x01)
		{
				D5_HIGH;
		}
		else
		{
				D5_LOW;
		}
		
		if ((value >> 2) & 0x01)
		{
				D6_HIGH;
		}
		else
		{
				D6_LOW;
		}
		
		if ((value >> 3) & 0x01)
		{
				D7_HIGH;
		}
		else
		{
				D7_LOW;
		}

    LCD_ENABLE_PULSE();
}

void LCD_COMMAND(uint8_t value)
{
    RS_LOW; // COMMAND
    LCD_WRITE_CHAR(value);
}

void LCD_COMMAND_4BIT(uint8_t value)
{
    RS_LOW; // COMMAND
    LCD_WRITE_NIBBLE(value);
}

void LCD_WRITE_8BIT(uint8_t value)
{
    RS_HIGH; // DATA
    LCD_WRITE_CHAR(value);
}

void LCD_SET_CURSOR(uint8_t col, uint8_t row)
{
    /*
    ************** Display Position ***************
    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
    -----------------------------------------------
    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
    40 41 42 43 44 45 46 47 48 49 4A 4B 4C 4D 4E 4F
    */
    uint8_t row_offsets[] = {0x00, 0x40};
    LCD_COMMAND(0x80 | (col + row_offsets[row]));
}

void LCD_SEND_STRING(char msg[32])
{
    uint8_t i = 0;
    while (msg[i] != '\0')
    {
        LCD_WRITE_8BIT((uint8_t) msg[i++]);
    }
}

void LCD_ENABLE_PULSE()
{
    EN_HIGH;
    T1_delay_ms(1);
    EN_LOW;
    T1_delay_ms(2); // Enable pulse must be > 37us to settle
}
