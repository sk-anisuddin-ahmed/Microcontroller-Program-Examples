#include <LPC213x.h>
#include <stdio.h>

void __irq ADC0_ISR(void) 
{
    unsigned result = (AD0DR2 >> 6) & 0x3FF; // 10-bit value channel 2 (AD0.2 on P0.28)	

	// Clear Interrupt Flag
	AD0STAT = 0;
    // Acknowledge VIC
    VICVectAddr = 0x00;
}

void ADC_INIT(void) 
{
							// Configure Pins to ADC Mode
    AD0CR = (1 << 2)        // select channel 2
          | (5 << 8)        // CLKDIV (PCLK/5 → ~12 MHz ADC clock)
          | (1 << 21)       // enable ADC
          | (6 << 24);      // START = 110 → trigger on MAT0.1
        //   | (1<<16)         // BURST=1 → continuous sampling

    // Enable interrupt for channel 2
    AD0INTEN = (1 << 2);

    // Configure VIC for ADC0 interrupt (channel 18)
    VICIntSelect &= ~(1 << 18);              // IRQ
    VICVectAddr0 = (unsigned long)ADC0_ISR;  // ISR address
    VICVectCntl0 = (1 << 5) | 18;            // enable slot 0, source=ADC0
    VICIntEnable = (1 << 18);                // enable ADC0 interrupt
}