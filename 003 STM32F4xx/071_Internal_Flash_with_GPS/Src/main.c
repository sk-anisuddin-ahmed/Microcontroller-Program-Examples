#include <stdio.h>
#include <stdint.h>
#include "itm.h"
#include "flash.h"
#include "gps.h"
#include "uart.h"
#include "sysTick.h"

int main(void)
{
	SysTick_Init();
	ITM_Init();
	UART2_Init();
	GPS_Init();

	while (1)
	{
		GPS_Task();
	}
}
