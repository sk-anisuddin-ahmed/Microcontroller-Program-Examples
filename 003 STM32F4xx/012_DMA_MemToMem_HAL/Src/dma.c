/*
 * dma.c
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#include "stm32f4xx_hal.h"
#include "dma.h"
#include <stdio.h>
#include <string.h>

DMA_HandleTypeDef hdma;

#define BUF_SIZE 4
static uint32_t dstBuf[BUF_SIZE];
static const uint32_t srcBuf[BUF_SIZE] = { 0xA, 0xB, 0xC, 0xD };

void HAL_DMA_XferCpltCallback(DMA_HandleTypeDef *hdma)
{
    printf("DMA Transfer Completed!\n");
    for (int i = 0; i < BUF_SIZE; i++)
    {
        printf("[%d] src=0x%08lX dst=0x%08lX\n", i, srcBuf[i], dstBuf[i]);
    }
}

void HAL_DMA_XferErrorCallback(DMA_HandleTypeDef *hdma)
{
    printf("DMA Transfer Error!\n");
}

void DMA_INIT (void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();

	hdma.Instance = DMA2_Stream0;
	hdma.Init.Channel = DMA_CHANNEL_0;
	hdma.Init.Direction = DMA_MEMORY_TO_MEMORY;
	hdma.Init.PeriphInc = DMA_PINC_ENABLE;
	hdma.Init.MemInc = DMA_MINC_ENABLE;
	hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	hdma.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	hdma.Init.Mode = DMA_NORMAL;
	hdma.Init.Priority = DMA_PRIORITY_HIGH;
	hdma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma);

	HAL_DMA_RegisterCallback(&hdma, HAL_DMA_XFER_CPLT_CB_ID, HAL_DMA_XferCpltCallback);
	HAL_DMA_RegisterCallback(&hdma, HAL_DMA_XFER_ERROR_CB_ID, HAL_DMA_XferErrorCallback);

	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	HAL_DMA_Start_IT(&hdma, (uint32_t) srcBuf, (uint32_t) dstBuf, BUF_SIZE);
}

void DMA2_Stream0_IRQHandler (void)
{
	HAL_DMA_IRQHandler(&hdma);
}
