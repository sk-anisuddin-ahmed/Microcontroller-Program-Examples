#include <stdint.h>
#include "itm.h"

void ITM_Init(void)
{
    DEMCR.TRCENA = 1;
    ITM_TER.STIM0 = 1;
}

void ITM_SendChar(uint8_t ch)
{
	while(!ITM_STIM_PORT0.READY);
    ITM_STIM_PORT0.DATA = ch;
}

int __io_putchar(int ch)
{
    ITM_SendChar((uint8_t)ch);
    return ch;
}
