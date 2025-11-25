#include <LPC213x.h>
#include <stdio.h>
#include <stdint.h>

void UART_INIT (void) 
{
									//Configure Pins to UART Mode
    U0LCR = 0x03;            		// 8 Bits
	U0LCR = 0x83;            		// 8N1, DLAB=1
    U0DLL = UART_BAUD_RATE(9600);  	// divisor for 9600 baud
	U0LCR = 0x03;            		// DLAB = 0
    U0FCR = 0x07;            		// FIFO enable and Cleared
}

void sendChar(uint8_t ch) 
{
    while (!(U0LSR & (1 << 5))); // wait for THR empty
    U0THR = ch;
}

int _write(int fd, const void *buf, size_t nbytes) 
{
    const uint8_t *p = (const uint8_t *)buf;
    if (fd == 1 || fd == 2) //1 - stdout / 2 - stderr
	{
        for (size_t i = 0; i < nbytes; i++) 
		{
            sendChar(p[i]);
        }
        return (int)nbytes;
    }
    return -1;
}