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
	SPI1_Send(tx1);
	printf("SPI1 Sent: 0x%02X\n", tx1);

	uint8_t rx1 = SPI1_Receive();
	printf("SPI1 Received: 0x%02X\n", rx1);

    while(1)
    {
		
    }
}
