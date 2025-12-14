/*
 * gps.c
 *
 *  Created on: 15-Dec-2025
 *      Author: skani
 */

#include <string.h>
#include <stdio.h>
#include "uart.h"
#include "flash.h"
#include "sysTick.h"

#define GPS_TIMEOUT_MS   1000U
#define GPS_SECTOR_INDEX 8U
#define GPS_FLASH_BASE   0x08080000U
#define GPS_FLASH_SIZE   (128U * 1024U)

char gps_buf[64];
uint32_t gps_ptr = GPS_FLASH_BASE;
uint32_t lastTick = 0;

void GPS_Init(void)
{
    printf("GPS Init\n");
    UART2_WriteString("AT\r\n");
    UART2_WriteString("AT+CGNSPWR=1\r\n");
    FLASH_EraseSector(GPS_SECTOR_INDEX);
    gps_ptr = GPS_FLASH_BASE;
    printf("Flash Erased\n");
}

int GPS_Query(void)
{
    int i = 0;
    UART2_WriteString("AT+CGNSINF\r\n");
    while (i < (int)(sizeof(gps_buf) - 1))
    {
        char c = UART2_ReadChar(GPS_TIMEOUT_MS);
        if (c == GSM_TIMEOUT_CHAR)
        {
        	printf("Timeout\n");
        	break;
        }
        gps_buf[i++] = c;
        if (c == '\n') break;
    }
    gps_buf[i] = '\0';
    printf("Resp %dB\n", i);
    return i;
}

void GPS_WriteToFlash(const char *data, uint32_t len)
{
    printf("Write %luB @0x%08lX\n", (unsigned long)len, (unsigned long)gps_ptr);
    const uint32_t *src = (const uint32_t*)data;
    uint32_t words = (len + 3U) / 4U;
    for (uint32_t i = 0; i < words; i++)
    {
        FLASH_WriteWord(gps_ptr, src[i]);
        gps_ptr += 4U;
        if (gps_ptr >= (GPS_FLASH_BASE + GPS_FLASH_SIZE))
        {
            FLASH_EraseSector(GPS_SECTOR_INDEX);
            gps_ptr = GPS_FLASH_BASE;
        }
    }
}

void GPS_Task(void)
{
    if ((msTicks - lastTick) >= 10000U)
    {
        lastTick = msTicks;
        int n = GPS_Query();
        if (n > 0)
        {
        	GPS_WriteToFlash(gps_buf, (uint32_t)n);
        }
    }
}
