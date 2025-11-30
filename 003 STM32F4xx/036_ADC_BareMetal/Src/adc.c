/*
 * adc.c
 *
 *  Created on: 30-Nov-2025
 *      Author: skani
 */

#include "adc.h"
#include "gpio.h"
#include "rcc.h"

void ADC1_Init(void)
{
    RCC.AHB1ENR.GPIOAEN = 1;
    RCC.APB2ENR.ADC1EN  = 1;

    GPIOA.MODER.PIN1 = GPIO_MODE_ANALOG;
    GPIOA.PUPDR.PIN1 = GPIO_NOPULL;

    ADC1.SMPR2.SMP1 = ADC_SAMPLE_56CYC;
    ADC1.SQR3.SQ1   = 1;
    ADC1.CR2.ADON   = 1;   // enable ADC
    while (ADC1.CR2.ADON == 0)
    {

    }
	for (volatile int i = 0; i < 1000; i++); // Warm-up time
}

uint16_t ADC1_Read(void)
{
    ADC1.CR2.SWSTART = 1;
    while (ADC1.SR.EOC == 0);
    return (uint16_t)ADC1.DR.DATA;
}
