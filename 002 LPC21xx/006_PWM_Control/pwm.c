#include <LPC213x.h>

void PWM_INIT(void) 
{
    PINSEL0 |= (1 << 1);   // P0.0 → PWM1

    PWMPR = 0;             // no prescale
    PWMMR0 = 400;         // period → 1.5 kHz
    PWMMR1 = 200;         // duty cycle = 50%

    PWMMCR = (1 << 1);     // reset on MR0
    PWMPCR = (1 << 9);     // enable PWM1 output
    PWMLER = (1 << 0) | (1 << 1); // latch MR0 and MR1

    PWMTCR = (1 << 0) | (1 << 3); // enable counter + PWM mode
}

void SET_DUTY(int duty_cycle)
{
    PWMMR1 = duty_cycle;   // duty cycle value (0..PWMMR0)
    PWMLER = (1 << 1);     // latch MR1 → update at next cycle
}
