/*
 * itm.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include "core_cm4.h"

int __io_putchar(int ch)
{
    ITM_SendChar((uint32_t)ch);
    return ch;
}

void ITM_Init()
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	ITM->TER |=  (1 << 0u);
	ITM->TCR |= ITM_TCR_ITMENA_Msk;
}
