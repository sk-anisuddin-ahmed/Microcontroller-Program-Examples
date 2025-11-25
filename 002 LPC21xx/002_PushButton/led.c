#include <LPC213x.h>

void LED_UPDATE(int val)
{
	_Bool LED1 = ((val & 0x01) > 0),
				LED2 = ((val & 0x02) > 0),
				LED3 = ((val & 0x04) > 0),
				LED4 = ((val & 0x08) > 0);
	
	if (LED1) IO0SET |= (1 << 0);
	else 			IO0CLR |= (1 << 0);
	
	if (LED2) IO0SET |= (1 << 5);
	else 			IO0CLR |= (1 << 5);
	
	if (LED3) IO0SET |= (1 << 10);
	else 			IO0CLR |= (1 << 10);
	
	if (LED4) IO0SET |= (1 << 15);
	else 			IO0CLR |= (1 << 15);
}
