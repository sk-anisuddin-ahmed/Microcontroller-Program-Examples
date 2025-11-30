#include <stdio.h>
#include <stdint.h>
#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "spi.h"
#include "itm.h"

int main(void)
{
	SysTick_Init();
	ITM_Init();
	SPI1_Init();

	uint8_t tx1 = 0xAB;
	printf("SPI1 Sent: 0x%02X\n", tx1);
	SPI1_Send(tx1);

    while(1)
    {
		
    }
}
