#include <LPC21xx.h>
#include "clock.h"
#include "pwm.h"
#include "timer.h"

int main ()
{	
		__disable_irq();	
		CLOCK_INIT();
		TIMER_INIT();
		PWM_INIT();	
		__enable_irq();	

		while (1) 
		{
				SET_DUTY(100);  // 25% duty
				T1_delay_ms(2500);

				SET_DUTY(200);  // 50% duty
				T1_delay_ms(2500);

				SET_DUTY(300);  // 75% duty
				T1_delay_ms(2500);

				SET_DUTY(400);  // 100% duty
				T1_delay_ms(2500);
		}
}
