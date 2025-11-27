/*
 * gpio.c
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#include <stdio.h>
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"
#include "exti.h"

void GPIO_Init ()
{
	RCC.AHB1ENR.GPIODEN = RCC_ENABLE;

	GPIOD.MODER.PIN12 = GPIO_MODE_OUTPUT;
	GPIOD.MODER.PIN13 = GPIO_MODE_OUTPUT;
	GPIOD.MODER.PIN14 = GPIO_MODE_OUTPUT;
	GPIOD.MODER.PIN15 = GPIO_MODE_OUTPUT;
}

void Button_Init(void)
{
    RCC.AHB1ENR.GPIOAEN = RCC_ENABLE;

    GPIOA.MODER.PIN0 = GPIO_MODE_INPUT;
    GPIOA.MODER.PIN0 = GPIO_MODE_INPUT;

    RCC.APB2ENR.SYSCFGEN = SYSCFGEN_ENABLE;
    SYSCFG.EXTICR1.EXTI0 = EXTI_PORT_A;

    EXTI.IMR.MR0   = EXTI_MASK_ENABLE;
    EXTI.RTSR.TR0  = EXTI_RISING_DISABLE;
    EXTI.FTSR.TR0  = EXTI_FALLING_ENABLE;

    NVIC.ISER[0].SETENA6 = NVIC_IRQ_ENABLE;
}

void EXTI0_IRQHandler(void)
{
	// Clear interrupt flag
	EXTI.PR.PR0 = 1;

	GPIOD.ODR.PIN12 ^= 1;
	GPIOD.ODR.PIN13 ^= 1;
	GPIOD.ODR.PIN14 ^= 1;
	GPIOD.ODR.PIN15 ^= 1;

	printf("User Pressed Button - PA0\n");
}
