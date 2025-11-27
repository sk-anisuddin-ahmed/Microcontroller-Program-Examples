#include <stdio.h>
#include <stdint.h>
#include "itm.h"
#include "sysTick.h"
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"

int main(void)
{
	SysTick_Init();
	ITM_Init();
	GPIO_Init();
	Button_Init();

    while(1)
    {

    }
}
