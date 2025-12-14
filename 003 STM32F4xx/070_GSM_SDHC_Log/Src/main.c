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
#include "log.h"

int main(void)
{
    SysTick_Init();
    ITM_Init();
    SPI2_Init();
    msDelay(2000);
	Logger_Init();
	Logger_OpenFile("0:/log.txt");
    UART2_Init();
    msDelay(1000);
    if (GSM_Init())
    {
    	GSM_Log_SDHC();
    }

    while (1)
    {

    }
}
