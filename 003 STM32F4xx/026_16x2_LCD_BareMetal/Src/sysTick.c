/*
 * sysTick.c
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#include <stdint.h>
#include "sysTick.h"

volatile uint32_t msTicks = 0;

void SysTick_Handler(void)
{
    msTicks++;
}

void SysTick_Init(void)
{
    SysTick->LOAD.RELOAD = (SystemCoreClock / 1000); // 1ms reload
    SysTick->VAL.CURRENT = 0;                            // clear counter

    SysTick->CTRL.ENABLE    = 1; // enable counter
    SysTick->CTRL.TICKINT   = 1; // enable interrupt
    SysTick->CTRL.CLKSOURCE = 1; // use CPU clock
}

void msDelay(uint32_t ms)
{
    uint32_t start = msTicks;
    while ((msTicks - start) < ms);
}
