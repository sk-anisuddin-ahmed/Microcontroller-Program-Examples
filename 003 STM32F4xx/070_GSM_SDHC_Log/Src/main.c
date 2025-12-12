#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "spi.h"
#include "uart.h"
#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "itm.h"
#include "sdcmd.h"
#include "gsm.h"

int main(void)
{
    SysTick_Init();
    ITM_Init();
    SPI2_Init();
    UART2_Init();
    msDelay(2000);
    if (GSM_Init())
    {
    	GSM_Log_SDHC();
    }

    while (1)
    {

    }
}
