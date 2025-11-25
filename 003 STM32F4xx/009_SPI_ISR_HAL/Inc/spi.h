/*
 * spi.h
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#ifndef SPI_H
#define SPI_H

#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef hspi1;

void SPI1_Init(void);

#endif /* SPI_H_ */
