#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "spi.h"
#include "itm.h"
#include "log.h"
#include "sdcmd.h"

int main(void)
{
    SysTick_Init();
    ITM_Init();
    SPI2_Init();
    msDelay(2000);

    Logger_Init();
    Logger_OpenFile("0:/log.txt");

    while (1)
    {

    }
}
