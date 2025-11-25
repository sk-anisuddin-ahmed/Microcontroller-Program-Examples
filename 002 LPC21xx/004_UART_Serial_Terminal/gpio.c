#include <LPC213x.h>
#include "gpio.h"

#define LED_PIN (1 << 10)

void LED_ON(void)  { IO0SET = LED_PIN; }
void LED_OFF(void) { IO0CLR = LED_PIN; }

void GPIO_INIT(void)
{
    //All pins set to GPIO
    PINSEL0 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;

    //All pins as input
    IO0DIR = 0x00000000;
    IO1DIR = 0x00000000;
	
		//Setting Desired Pin 0 as output
		IO0DIR |= LED_PIN;      // P0.10 as output
    IO0CLR  = LED_PIN;      // LED off initially
}
