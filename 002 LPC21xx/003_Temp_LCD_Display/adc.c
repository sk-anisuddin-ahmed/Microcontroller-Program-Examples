#include <LPC213x.h>
#include <stdio.h>

int temp_adc = 0;

void ADC_Value_Fetch ()
{
		AD0CR |= (1 << 24);      														// START = Manual Timer Trigger
		while (!(temp_adc & ((unsigned long)1 << 31)))			// wait until DONE bit is set
		{
				temp_adc = AD0DR;
		}
		
		//Wait untill the DONE bits Sets
		AD0CR &= ~(1 << 24);																	//Stops the A/D Conversion
	
		temp_adc = (AD0DR >> 6) & 0x3FF; 									// 10-bit value channel 0 (AD0.0 on P0.27)
		AD0CR &= ~(1 << 24);
}

void ADC_POLLING_INIT (void)
{
    PINSEL1 |=   (0x01 << 22);   // set 01 → AD0.27

    AD0CR = (1 << 0)        // select channel 0
					|	(14 << 8)				// Clock Div
          | (1 << 21);      // enable ADC
}
