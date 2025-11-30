/*
 * uart.c
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include "rcc.h"
#include "uart.h"
#include "nvic.h"
#include "gpio.h"
#include "dma.h"

#define FCLK	16000000
#define UART_BRR(BAUD)   	 (double)((FCLK / (16.0 * BAUD)))
#define UART_BRR_MANT(BAUD)  ((uint32_t)UART_BRR(BAUD))
#define UART_BRR_FRAC(BAUD)  ((uint32_t)(((UART_BRR(BAUD) - UART_BRR_MANT(BAUD)) * 16) + 0.5))

uint8_t DMA_RxBuffer[8];

void UART2_DMA_Init(void)
{
    RCC.AHB1ENR.GPIOAEN = 1;
    RCC.AHB1ENR.DMA1EN  = 1;
    RCC.APB1ENR.USART2EN = 1;

    GPIOA.MODER.PIN2 = GPIO_MODE_AF;  // PA2 = TX
    GPIOA.MODER.PIN3 = GPIO_MODE_AF;  // PA3 = RX

    GPIOA.AFRL.AFR2 = 7;
    GPIOA.AFRL.AFR3 = 7;

    USART2.BRR.DIV_Mantissa = UART_BRR_MANT(115200);
    USART2.BRR.DIV_Fraction = UART_BRR_FRAC(115200);

	/* DMA1 Stream5 USART2_RX */
    DMA1.STREAM5.CR.EN = 0;
	while (DMA1.STREAM5.CR.EN)
	{

	}

    DMA1.HIFCR.FEIF5  = 1;
    DMA1.HIFCR.DMEIF5 = 1;
    DMA1.HIFCR.TEIF5  = 1;
    DMA1.HIFCR.HTIF5  = 1;
    DMA1.HIFCR.TCIF5  = 1;

    DMA1.STREAM5.CR.TCIE = 1;
    DMA1.STREAM5.CR.TEIE = 1;

    DMA1.STREAM5.CR.CHSEL = DMA_CH4;
	DMA1.STREAM5.CR.MINC  = DMA_MEM_INC_ENABLE;
	DMA1.STREAM5.CR.PINC  = DMA_DISABLE;
	DMA1.STREAM5.CR.CIRC  = DMA_ENABLE;
	DMA1.STREAM5.CR.DIR   = DMA_DIR_PERIPH_TO_MEM;
	DMA1.STREAM5.CR.PL    = DMA_PRIORITY_MEDIUM;

	DMA1.STREAM5.FCR.DMDIS = 0;   // Enable Direct Mode
	DMA1.STREAM5.FCR.FTH   = 0;   // FIFO threshold irrelevant now

	DMA1.STREAM5.NDTR = sizeof(DMA_RxBuffer);
	DMA1.STREAM5.PAR  = (uint32_t)&USART2.DR;
	DMA1.STREAM5.M0AR = (uint32_t)DMA_RxBuffer;

	DMA1.STREAM5.CR.EN = 1;

    /* DMA1 Stream6 USART2_TX */
	DMA1.STREAM6.CR.EN = 0;
	while (DMA1.STREAM6.CR.EN)
	{

	}

	DMA1.HIFCR.FEIF6  = 1;
	DMA1.HIFCR.DMEIF6 = 1;
	DMA1.HIFCR.TEIF6  = 1;
	DMA1.HIFCR.HTIF6  = 1;
	DMA1.HIFCR.TCIF6  = 1;

	DMA1.STREAM6.CR.TCIE = 1;
	DMA1.STREAM6.CR.TEIE = 1;

    DMA1.STREAM6.CR.CHSEL = DMA_CH4;
	DMA1.STREAM6.CR.MINC  = DMA_MEM_INC_ENABLE;
	DMA1.STREAM6.CR.PINC  = DMA_DISABLE;
	DMA1.STREAM6.CR.CIRC  = DMA_DISABLE;
	DMA1.STREAM6.CR.DIR   = DMA_DIR_MEM_TO_PERIPH;
	DMA1.STREAM6.CR.PL    = DMA_PRIORITY_MEDIUM;

	DMA1.STREAM6.PAR = (uint32_t)&USART2.DR;

	NVIC.ISER[0].SETENA16 = 1;
	NVIC.ISER[0].SETENA17 = 1;

	USART2.CR1.RE   = 1;
	USART2.CR1.TE   = 1;
	USART2.CR3.DMAR = DMA_ENABLE; // RX DMA request
	USART2.CR3.DMAT = DMA_ENABLE; // TX DMA request
	USART2.CR1.UE   = 1;
}

void UART2_DMA_Send(uint8_t *data, uint16_t len)
{
    DMA1.STREAM6.CR.EN = 0;
    while (DMA1.STREAM6.CR.EN)
    {

    }

    /* Clear flags */
    DMA1.HIFCR.FEIF6  = 1;
    DMA1.HIFCR.DMEIF6 = 1;
    DMA1.HIFCR.TEIF6  = 1;
    DMA1.HIFCR.HTIF6  = 1;
    DMA1.HIFCR.TCIF6  = 1;

    DMA1.STREAM6.M0AR = (uint32_t)data;
    DMA1.STREAM6.NDTR = (uint32_t)len;

    DMA1.STREAM6.CR.EN = 1;
}

void DMA1_Stream5_IRQHandler(void)
{
    if (DMA1.HISR.TCIF5)
    {
        DMA1.HIFCR.TCIF5 = 1;
        UART2_DMA_Send(DMA_RxBuffer, sizeof(DMA_RxBuffer));
    }

    DMA1.HIFCR.FEIF5  = 1;
	DMA1.HIFCR.DMEIF5 = 1;
	DMA1.HIFCR.TEIF5  = 1;
	DMA1.HIFCR.HTIF5  = 1;
}

void DMA1_Stream6_IRQHandler(void)
{
    if (DMA1.HISR.TCIF6)
    {
        DMA1.HIFCR.TCIF6 = 1;
    }
    if (DMA1.HISR.TEIF6)
    {
        DMA1.HIFCR.TEIF6 = 1;
    }
}

