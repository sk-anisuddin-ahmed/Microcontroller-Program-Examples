#include <LPC213x.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "uart.h"
#include "timer.h"

void UART_INIT (void) 
{
		unsigned int divisor;
	
		/*Configure Pins to UART Mode*/
		PINSEL0 &= ~0x0000000F;   		// clear bits 0–3
		PINSEL0 |=  0x00000005;   		// set P0.0=TXD0, P0.1=RXD0
																
    U0LCR = 0x03;            				// 8 Bits
		U0LCR = 0x83;            				// 8N1, DLAB=1
	
    // Baud rate divisor for 9600 baud    
		divisor = UART_BAUD_RATE(9600);
    U0DLL = divisor & 0xFF;
    U0DLM = (divisor >> 8);
		U0LCR = 0x03;            				// DLAB = 0
    U0FCR = 0x07;            				// FIFO enable and Cleared
}

void sendChar(uint8_t ch) 
{
    while (!(U0LSR & (1 << 5))); // wait for THR empty
    U0THR = ch;
}

void sendStr(char *buf, int len) 
{
		int i;
		for (i = 0; i < len; i++) 
		{
				sendChar(buf[i]);
		}
}

unsigned char recChar()
{
    while ((U0LSR & 1) == 0);   // Wait until data is available
    return U0RBR;               // Return received byte
}
