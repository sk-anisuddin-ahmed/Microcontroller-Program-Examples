#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "spi.h"
#include "itm.h"
#include "sdcmd.h"

uint8_t buff[512];

int main(void)
{
    SysTick_Init();
    ITM_Init();
    SPI2_Init();
    msDelay(2000);

    if (SD_Init() == 0)
    {
    	SD_ReadBlock(buff, 1);
    }
    else
    {
    	printf("SD Init Failed\n");
    }

    while (1)
    {

    }
}
