#include <LPC213x.h>
#include "timer.h"

void T1_delay_ms (int delay_ms)
{
		T1TC = 0;			// Reset Counter
    while (T1TC < delay_ms);
}

void TIMER_INIT(void)
{
    T1TCR = 0x02;          			 // Reset Timer1
    T1PR  = TIMER_PERIOD_MS(1);  // Prescaler for 1 ms tick
    T1TCR = 0x01;           		 // Enable Timer1
}
