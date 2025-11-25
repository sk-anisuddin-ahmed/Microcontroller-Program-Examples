/*
 * uart.h
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#ifndef UART_H
#define UART_H

#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;
extern uint8_t rxBuf[];
extern uint8_t txBuf[];

void UART_DMA_Init(void);

#endif /* UART_H_ */
