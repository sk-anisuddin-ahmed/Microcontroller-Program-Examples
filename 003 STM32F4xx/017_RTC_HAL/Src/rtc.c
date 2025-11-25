/*
 * rtc.c
 *  Created on: 26-Nov-2025
 */

#include "rtc.h"
#include <stdio.h>

RTC_HandleTypeDef hrtc;

void RTC_INIT(void)
{
    /* Enable PWR clock and access */
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();

    /* Enable LSI (internal 32 kHz RC oscillator) */
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
    RCC_OscInitStruct.LSIState       = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;

    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* Select LSI as RTC Clock */
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.RTCClockSelection    = RCC_RTCCLKSOURCE_LSI;

    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    /* Enable RTC Clock */
    __HAL_RCC_RTC_ENABLE();

    /* Configure RTC */
    hrtc.Instance = RTC;
    hrtc.Init.HourFormat     = RTC_HOURFORMAT_24;
    hrtc.Init.AsynchPrediv   = 127;
    hrtc.Init.SynchPrediv    = 249;     // correct for ~32kHz LSI
    hrtc.Init.OutPut         = RTC_OUTPUT_DISABLE;

    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        printf("RTC Init failed!\n");
    }

    /* Set time & date on every boot*/
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sTime.Hours   = 12;
    sTime.Minutes = 34;
    sTime.Seconds = 0;

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

    sDate.WeekDay = RTC_WEEKDAY_WEDNESDAY;
    sDate.Month   = RTC_MONTH_NOVEMBER;
    sDate.Date    = 26;
    sDate.Year    = 25;

    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void RTC_Read(void)
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    printf("RTC Time: %02d:%02d:%02d | Date: %02d-%02d-%04d\n",
           sTime.Hours,
           sTime.Minutes,
           sTime.Seconds,
           sDate.Date,
           sDate.Month,
           2000 + sDate.Year);
}
