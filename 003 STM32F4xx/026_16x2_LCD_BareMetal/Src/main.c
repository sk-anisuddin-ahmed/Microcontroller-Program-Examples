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
	LCD_CLEAR();
	LCD_SET_CURSOR(0, 0);
	LCD_SEND_STRING("Hello India");
	LCD_SET_CURSOR(0, 1);
	LCD_SEND_STRING("I'm Anis *_*");

    while(1)
    {

    }
}
