#include <stdio.h>
#include <stdint.h>
#include "itm.h"
#include "sysTick.h"
#include "rcc.h"
#include "gpio.h"
#include "lcd.h"

int main(void)
{
	SysTick_Init();

	LCD_BEGIN();
	msDelay(1000);
	LCD_CLEAR();
	LCD_CLEAR();
	LCD_SET_CURSOR(0, 1);
	LCD_SEND_STRING("STARTING.....");

    while(1)
    {

    }
}
