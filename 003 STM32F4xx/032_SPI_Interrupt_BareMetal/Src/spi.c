/*
 * spi.c
 *
 *  Created on: 30-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include <stdint.h>
#include "gpio.h"
#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "spi.h"

uint8_t rxSPI;

void SPI1_Init(void)
{
	RCC.AHB1ENR.GPIOAEN = 1;   // GPIOA clock
	RCC.APB2ENR.SPI1EN  = 1;   // SPI1 clock

	GPIOA.MODER.PIN5 = GPIO_MODE_AF;
	GPIOA.MODER.PIN6 = GPIO_MODE_AF;
	GPIOA.MODER.PIN7 = GPIO_MODE_AF;

	GPIOA.AFRL.AFR5 = 5; // AF5 for SPI1
	GPIOA.AFRL.AFR6 = 5;
	GPIOA.AFRL.AFR7 = 5;

	GPIOA.OSPEEDR.PIN5 = GPIO_SPEED_HIGH;
	GPIOA.OSPEEDR.PIN6 = GPIO_SPEED_HIGH;
	GPIOA.OSPEEDR.PIN7 = GPIO_SPEED_HIGH;

	GPIOA.PUPDR.PIN5 = GPIO_NOPULL;
	GPIOA.PUPDR.PIN6 = GPIO_NOPULL;
	GPIOA.PUPDR.PIN7 = GPIO_NOPULL;

	SPI1.CR1.SSM  = 1;   // software NSS
	SPI1.CR1.SSI  = 1;   // internal NSS high
	SPI1.CR1.MSTR = 1;   // master
	SPI1.CR1.BR   = 3;   // fPCLK/16
	SPI1.CR1.CPOL = 0;   // polarity low
	SPI1.CR1.CPHA = 0;   // phase first edge
	SPI1.CR1.DFF  = 0;   // 8-bit
	SPI1.CR1.SPE  = 1;   // enable SPI

	SPI1.CR2.TXEIE = 0;
	SPI1.CR2.RXNEIE = 1;

	NVIC.ISER[1].SETENA3 = 1;
}

void SPI1_Send(uint8_t data)
{
    while (SPI1.SR.TXE == 0);   // wait until TX buffer empty
    SPI1.DR.DR = data;          // write data
    while (SPI1.SR.BSY == 1);   // wait until not busy
}

void SPI1_IRQHandler(void)
{
    if (SPI1.SR.RXNE)
    {
    	rxSPI = (uint8_t)SPI1.DR.DR;
    	printf("SPI1 Received: 0x%02X\n", rxSPI);
    }

    if (SPI1.SR.OVR)
    {
        (void)SPI1.DR.DR;
        (void)SPI1.SR;
    }
}
