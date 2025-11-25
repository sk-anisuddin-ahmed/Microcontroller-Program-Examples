#include <LPC21xx.h>
#include <string.h>
#include "clock.h"
#include "gpio.h"
#include "uart.h"
#include "timer.h"

char buf[32];
int idx = 0;

int main ()
{	
	__disable_irq();	
	CLOCK_INIT();
	GPIO_INIT();
	UART_INIT();
	TIMER_INIT();
	__enable_irq();	
	
	sendStr("UART LED Control Ready\r\n", 25);
	
	while(1)
	{
			// receive one character
			unsigned char c = recChar();
			if (c == '\r' || c == '\n') 
			{
					buf[idx] = '\0';   // terminate string

					if (strcmp(buf, "LEDON") == 0) 
						{
							LED_ON();
							sendStr("LED turned ON\r\n", 15);
					} 
					else if (strcmp(buf, "LEDOFF") == 0)
					{
							LED_OFF();
							sendStr("LED turned OFF\r\n", 16);
					} 
					else 
					{
							sendStr("Unknown command\r\n", 18);
					}

					idx = 0; // reset buffer
			} 
			else 
				{
					if (idx < sizeof(buf)-1) 
					{
							buf[idx++] = c;
					}
			}
	}
}
