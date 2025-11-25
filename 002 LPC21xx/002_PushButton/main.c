#include <LPC21xx.h>
#include "clock.h"
#include "gpio.h"
#include "eirq.h"

/*
Bit 0 - P0.0
Bit 1 - P0.5
Bit 2 - P0.10
Bit 3 - P0.15

Push Button - P0.16
*/

int main ()
{	
	__disable_irq();	
	CLOCK_INIT();
	GPIO_INIT();	
	EINT();
	__enable_irq();	
	while(1);
	
	return 0;
}