#include <stdio.h>
#include <stdint.h>
#include "rcc.h"
#include "nvic.h"
#include "itm.h"
#include "tim.h"

int main(void)
{
	ITM_Init();
	TIM2_Init();

    while(1)
    {
    	if (tim2Flag)
    	{
    		printf("1 second Elapsed\n");
    		tim2Flag = 0;
    	}
    }
}
