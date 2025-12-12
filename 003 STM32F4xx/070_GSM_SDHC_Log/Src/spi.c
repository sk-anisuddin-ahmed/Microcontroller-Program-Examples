/*
 * spi.c
 *
 *  Created on: 30-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "sysTick.h"
#include "rcc.h"
#include "nvic.h"
#include "spi.h"

void SPI2_Init(void)
{
	// Enable clocks
	RCC.AHB1ENR.GPIOBEN = 1; // Enable GPIOB clock
	RCC.APB1ENR.SPI2EN = 1;	 // Enable SPI2 clock

	// Configure PB13=SCK, PB14=MISO, PB15=MOSI
	GPIOB.MODER.PIN13 = GPIO_MODE_AF;
	GPIOB.MODER.PIN14 = GPIO_MODE_AF;
	GPIOB.MODER.PIN15 = GPIO_MODE_AF;

	GPIOB.AFRH.AFR13 = 5; // AF5 for SPI2
	GPIOB.AFRH.AFR14 = 5;
	GPIOB.AFRH.AFR15 = 5;

	GPIOB.OSPEEDR.PIN13 = GPIO_SPEED_HIGH;
	GPIOB.OSPEEDR.PIN14 = GPIO_SPEED_HIGH;
	GPIOB.OSPEEDR.PIN15 = GPIO_SPEED_HIGH;

	GPIOB.PUPDR.PIN13 = GPIO_NOPULL;
	GPIOB.PUPDR.PIN14 = GPIO_NOPULL;
	GPIOB.PUPDR.PIN15 = GPIO_NOPULL;

	// Configure CS pin (PB12) as GPIO output
	GPIOB.MODER.PIN12 = GPIO_MODE_OUTPUT;
	GPIOB.OSPEEDR.PIN12 = GPIO_SPEED_HIGH;
	GPIOB.PUPDR.PIN12 = GPIO_NOPULL;
	GPIOB.ODR.PIN12 = 1;

	// SPI2 settings
	SPI2.CR1.SSM = 1;  // software NSS
	SPI2.CR1.SSI = 1;  // internal NSS high
	SPI2.CR1.MSTR = 1; // master
	SPI2.CR1.BR = 4;   // fPCLK/64 → ~200–400 kHz
	SPI2.CR1.CPOL = 0; // polarity low
	SPI2.CR1.CPHA = 0; // phase first edge
	SPI2.CR1.DFF = 0;  // 8-bit
	SPI2.CR1.SPE = 1;  // enable SPI
}

void SPI_CS_Control(bool state)
{
	GPIOB.ODR.PIN12 = state;
	printf("CS: %s\n", (state) ? "HIGH" : "LOW");
}

uint8_t SPI_Transfer(uint8_t data)
{
    // Wait until TX buffer empty
    while (!SPI2.SR.TXE);
    // Send data
    SPI2.DR = data;
    // Wait until RX buffer not empty
    while (!SPI2.SR.RXNE)
    {

    }
	// wait until not busy
	while (SPI2.SR.BSY == 1)
	{

	}
    // Read received data
    return (uint8_t)SPI2.DR;
}
