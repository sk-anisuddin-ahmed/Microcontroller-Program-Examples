#include <LPC21xx.h>
#include "clock.h"
#include "timer.h"
#include "gpio.h"

int main ()
{	
	CLOCK_INIT();
	GPIO_INIT();
	TIMER_ISR_INIT();
	__enable_irq();
	
	while(1);
	
	return 0;
}