/*
 * uart.h
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include "stm32f4xx_hal.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

#define BUF_SIZE 32
uint8_t rxBuf[BUF_SIZE];
uint8_t txBuf[BUF_SIZE] = "Hello from DMA UART\n";

void UART_DMA_Init (void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_ENABLE();

	// PA2 = TX, PA3 = RX
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&huart2);

	// USART2 RX DMA
	hdma_usart2_rx.Instance = DMA1_Stream5;
	hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
	hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
	hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&hdma_usart2_rx);
	__HAL_LINKDMA(&huart2, hdmarx, hdma_usart2_rx);

	// USART2 TX DMA
	hdma_usart2_tx.Instance = DMA1_Stream6;
	hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
	hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_usart2_tx.Init.Mode = DMA_NORMAL;
	hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&hdma_usart2_tx);
	__HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);

	// NVIC for DMA
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0); //RX
	HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0); //TX
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

	// Start DMA Reception
	HAL_UART_Transmit_DMA(&huart2, txBuf, strlen((char*)txBuf));
	HAL_UART_Receive_DMA(&huart2, rxBuf, BUF_SIZE);
}

void USART2_IRQHandler (void)
{
	HAL_UART_IRQHandler(&huart2);
}

void DMA1_Stream5_IRQHandler (void)
{
	HAL_DMA_IRQHandler(&hdma_usart2_rx);
}

void DMA1_Stream6_IRQHandler (void)
{
	HAL_DMA_IRQHandler(&hdma_usart2_tx);
}

void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		printf("DMA RX: %s\n", rxBuf);
		HAL_UART_Transmit_DMA(&huart2, rxBuf, strlen((char*)rxBuf));
	}
}

void HAL_UART_TxCpltCallback (UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		printf("DMA TX Complete\n");
	}
}
