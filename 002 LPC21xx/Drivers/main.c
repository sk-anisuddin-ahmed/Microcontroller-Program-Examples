#include <LPC21xx.h>
#include "clock.h"
#include "timer.h"
#include "gpio.h"

int main ()
{	
	__disable_irq();	
	CLOCK_INIT();
	
	
	__enable_irq();	
	while(1);
	
	return 0;
}