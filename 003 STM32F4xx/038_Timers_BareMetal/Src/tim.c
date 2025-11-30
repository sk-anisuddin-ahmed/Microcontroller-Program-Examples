/*
 * tim.c
 *
 *  Created on: 30-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include <stdint.h>
#include "rcc.h"
#include "nvic.h"
#include "itm.h"
#include "tim.h"

_Bool tim2Flag;

void TIM2_Init(void)
{
    RCC.APB1ENR.TIM2EN = 1;

    TIM2.PSC = 16000;
	TIM2.ARR = 1000;

    TIM2.DIER.UIE = 1;
    TIM2.CR1.CEN = 1;

    NVIC.ISER[0].SETENA28 = 1;
}

void TIM2_IRQHandler(void)
{
    TIM2.SR.UIF = 0;
    tim2Flag = 1;
}

