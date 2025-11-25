#include <LPC21xx.h>
#include <stdio.h>
#include <string.h>
#include "clock.h"
#include "timer.h"
#include "gpio.h"
#include "lcd.h"

const char * Password = "007";
char user_pass[16], id;

char KEYPAD_SCAN(void) 
	{
    const char keys[4][3] = 
		{
        {'1','2','3'},
        {'4','5','6'},
        {'7','8','9'},
        {'*','0','#'}
    };

		int row = 0;
    for (row = 0; row < 4; row++)
		{
        // Drive all rows HIGH
        IO0SET |= (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6);
        // Drive current row LOW
        IO0CLR |= (1 << (3 + row));

        T1_delay_ms(100);

        // Digital read of columns
        if (!(IO0PIN & (1 << 2))) return keys[row][0]; // Col1
        if (!(IO0PIN & (1 << 1))) return keys[row][1]; // Col2
        if (!(IO0PIN & (1 << 0))) return keys[row][2]; // Col3
    }
    return 0; // no key pressed
}

int main(void)
{   
    __disable_irq();
    CLOCK_INIT();
    GPIO_INIT();
    TIMER_INIT();
    LCD_BEGIN();
    __enable_irq();
    
    LCD_CLEAR();
    LCD_SET_CURSOR(0, 0);
    LCD_SEND_STRING("LOCKED");
    
    while(1)
    {
				char key = KEYPAD_SCAN();
        if (key) 
				{
            if (id < (sizeof(Password) - 1)) 
						{
                user_pass[id++] = key;
                user_pass[id] = '\0';
								key = 0;
            }

            // show typed password on 2nd row
            LCD_SET_CURSOR(0,1);
            LCD_SEND_STRING(user_pass);

            // check password
            if (strcmp(user_pass, Password) == 0)
						{
                LCD_CLEAR();
                LCD_SET_CURSOR(0,0);
                LCD_SEND_STRING("UNLOCKED");
                id = 0;
                user_pass[0] = '\0';
								break;
            }
						
						if (id >= (sizeof(Password) - 1))
						{
								id = 0;
								key = 0;
								user_pass[0] = '\0';
							
								LCD_CLEAR();
								LCD_SET_CURSOR(0, 0);
								LCD_SEND_STRING("LOCKED");
						}
        }
		}
		
		while(1);
}
