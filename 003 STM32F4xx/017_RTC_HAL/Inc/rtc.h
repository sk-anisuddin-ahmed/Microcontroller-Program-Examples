/*
 * rtc.h
 *
 *  Created on: 26-Nov-2025
 *      Author: skani
 */

#ifndef RTC_H_
#define RTC_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rtc.h"

extern RTC_HandleTypeDef hrtc;

void RTC_INIT(void);
void RTC_Read(void);

#endif /* RTC_H_ */
