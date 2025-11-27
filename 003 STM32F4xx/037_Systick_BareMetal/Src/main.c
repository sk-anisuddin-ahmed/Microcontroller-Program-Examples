#include <stdio.h>
#include <stdint.h>
#include "itm.h"
#include "sysTick.h"

int main(void)
{
	SysTick_Init();
	ITM_Init();

    while(1)
    {
    	printf("1 Senond Elapsed!\n");
    	msDelay(1000);
    }
}
