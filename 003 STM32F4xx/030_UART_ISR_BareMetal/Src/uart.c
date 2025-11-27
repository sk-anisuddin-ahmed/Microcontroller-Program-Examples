/*
 * uart.c
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include "rcc.h"
#include "uart.h"
#include "gpio.h"
#include "nvic.h"

#define FCLK	16000000
#define UART_BRR(BAUD)   	 (double)((FCLK / (16.0 * BAUD)))
#define UART_BRR_MANT(BAUD)  ((uint32_t)UART_BRR(BAUD))
#define UART_BRR_FRAC(BAUD)  ((uint32_t)(((UART_BRR(BAUD) - UART_BRR_MANT(BAUD)) * 16) + 0.5))

void UART2_Init(void)
{
    RCC.AHB1ENR.GPIOAEN = RCC_ENABLE;
    RCC.APB1ENR.USART2EN = RCC_ENABLE;

    GPIOA.MODER.PIN2 = GPIO_MODE_AF;
    GPIOA.MODER.PIN3 = GPIO_MODE_AF;

    /*  PA2 = AF7 (Tx), PA3 = AF7 (Rx) */
    GPIOA.AFRL.AFR2 = 7;  // AF7 for USART2
    GPIOA.AFRL.AFR3 = 7;

    GPIOA.PUPDR.PIN2 = GPIO_PULLUP;
    GPIOA.PUPDR.PIN3 = GPIO_PULLUP;

    GPIOA.OSPEEDR.PIN2 = GPIO_SPEED_HIGH;
    GPIOA.OSPEEDR.PIN3 = GPIO_SPEED_HIGH;

    USART2.BRR.DIV_Mantissa = UART_BRR_MANT(115200);
    USART2.BRR.DIV_Fraction = UART_BRR_FRAC(115200);

    USART2.CR1.RXNEIE = 1;

    USART2.CR1.TE = 1;
    USART2.CR1.RE = 1;
    USART2.CR1.UE = 1;

    NVIC.ISER[1].SETENA6 = 1;
}

char UART2_ReadChar(void)
{
    while (USART2.SR.RXNE == 0);
    return (char)USART2.DR.DR;
}

char rxBuf[32];
int ind;
_Bool rxRec;
void USART2_IRQHandler(void)
{
    rxBuf[ind++] = (char)USART2.DR.DR;
    ind = ind % 32;
    rxBuf[ind] = '\0';
    rxRec = 1;
}

void UART2_WriteChar(char c)
{
    while (USART2.SR.TXE == 0);
    USART2.DR.DR = (uint32_t)c;
}

char __io_putchar (char ch)
{
	UART2_WriteChar(ch);
	return ch;
}
