#include <LPC213x.h>
#include "pwm.h"

void PWM_INIT(void) 
{
    // Configure PWM pin-x as PWM1

    PWMPR = 0;           // no prescale
    PWMMR0 = 4000;       // period → 15 kHz
    PWMMR1 = 2000;       // duty cycle = 50%

    PWMMCR = (1<<0)|(1<<1); // interrupt + reset on MR0
    PWMPCR = (1<<9);        // enable PWM1 output
    PWMLER = (1<<0)|(1<<1); // latch MR0 and MR1

    PWMTCR = (1<<0)|(1<<3); // enable counter + PWM mode

    // VIC setup for PWM interrupt (source #8)
    VICIntSelect &= ~(1<<8);                  // IRQ
    VICVectAddr0 = (unsigned long)PWM_ISR;    // ISR address
    VICVectCntl0 = (1<<5) | 8;                // enable slot 0, source=PWM0
    VICIntEnable = (1<<8);                    // enable PWM interrupt
}

void SET_DUTY(int duty_cycle)
{
    PWMMR1 = duty_cycle;    // duty cycle value
    PWMLER = (1<<1);        // latch MR1 → update at next cycle
}

void __irq PWM_ISR(void)
{
    // Clear MR0 interrupt flag
    PWMIR = (1<<0);

    // Acknowledge VIC
    VICVectAddr = 0;
}
