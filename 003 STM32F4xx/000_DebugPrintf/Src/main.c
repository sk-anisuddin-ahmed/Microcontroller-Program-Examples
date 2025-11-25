#include <stdio.h>
#include <stdint.h>
#include "itm.h"

int main(void)
{
	SWO_Init();

    while(1)
    {
    	printf("Hello World\n");
    }
}
