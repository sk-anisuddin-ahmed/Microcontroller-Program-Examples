#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "itm.h"
#include "sysTick.h"
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"
#include "uart.h"
#include "gsm.h"

char gsmResp[128];

int main(void)
{
	SysTick_Init();
	ITM_Init();
	UART2_Init();
	GSM_Init();

	while(1)
	{
		GSM_ReadLine(gsmResp, sizeof(gsmResp));
		if (strlen(gsmResp) > 0)
		{
			GSM_Log(gsmResp);
		}
	}
}
