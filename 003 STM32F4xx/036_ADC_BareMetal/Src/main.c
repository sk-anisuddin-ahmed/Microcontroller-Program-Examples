#include <stdio.h>
#include <stdint.h>
#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "itm.h"
#include "adc.h"

int main(void)
{
	SysTick_Init();
	ITM_Init();
	ADC1_Init();

    while(1)
    {
		printf("ADC1: %d\n", ADC1_Read());
    	msDelay(1000);
    }
}
