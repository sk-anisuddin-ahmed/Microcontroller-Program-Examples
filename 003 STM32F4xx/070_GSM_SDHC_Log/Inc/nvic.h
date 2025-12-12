/*
 * nvic.h
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#ifndef NVIC_H_
#define NVIC_H_

typedef struct {
    volatile uint32_t SETENA0  :1;
    volatile uint32_t SETENA1  :1;
    volatile uint32_t SETENA2  :1;
    volatile uint32_t SETENA3  :1;
    volatile uint32_t SETENA4  :1;
    volatile uint32_t SETENA5  :1;
    volatile uint32_t SETENA6  :1;
    volatile uint32_t SETENA7  :1;
    volatile uint32_t SETENA8  :1;
    volatile uint32_t SETENA9  :1;
    volatile uint32_t SETENA10 :1;
    volatile uint32_t SETENA11 :1;
    volatile uint32_t SETENA12 :1;
    volatile uint32_t SETENA13 :1;
    volatile uint32_t SETENA14 :1;
    volatile uint32_t SETENA15 :1;
    volatile uint32_t SETENA16 :1;
    volatile uint32_t SETENA17 :1;
    volatile uint32_t SETENA18 :1;
    volatile uint32_t SETENA19 :1;
    volatile uint32_t SETENA20 :1;
    volatile uint32_t SETENA21 :1;
    volatile uint32_t SETENA22 :1;
    volatile uint32_t SETENA23 :1;
    volatile uint32_t SETENA24 :1;
    volatile uint32_t SETENA25 :1;
    volatile uint32_t SETENA26 :1;
    volatile uint32_t SETENA27 :1;
    volatile uint32_t SETENA28 :1;
    volatile uint32_t SETENA29 :1;
    volatile uint32_t SETENA30 :1;
    volatile uint32_t SETENA31 :1;
} NVIC_ISER_t;

typedef struct {
    NVIC_ISER_t ISER[8];   // ISER0..ISER7
} NVIC_t;

#define NVIC   (*(volatile NVIC_t *)0xE000E100)

typedef enum {
    NVIC_IRQ_DISABLE = 0,
    NVIC_IRQ_ENABLE  = 1
} NVIC_IRQ_EnableState_t;

#endif /* NVIC_H_ */
