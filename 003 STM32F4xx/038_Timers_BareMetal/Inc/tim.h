/*
 * tim.h
 *
 *  Created on: 30-Nov-2025
 *      Author: skani
 */

#ifndef TIM_H_
#define TIM_H_

#include <stdint.h>

typedef struct
{
    volatile uint32_t CEN     :1;   // Counter enable
    volatile uint32_t UDIS    :1;   // Update disable
    volatile uint32_t URS     :1;   // Update request source
    volatile uint32_t OPM     :1;   // One-pulse mode
    volatile uint32_t DIR     :1;   // Direction (0=up counter)
    volatile uint32_t CMS     :2;   // Center-aligned mode
    volatile uint32_t ARPE    :1;   // Auto-reload preload enable
    volatile uint32_t CKD     :2;   // Clock division
    volatile uint32_t RESERVED:22;
} TIM_CR1_t;

typedef struct
{
    volatile uint32_t UIE     :1;  // Update interrupt enable
    volatile uint32_t RESERVED:31;
} TIM_DIER_t;

typedef struct
{
    volatile uint32_t UIF     :1;  // Update interrupt flag
    volatile uint32_t RESERVED:31;
} TIM_SR_t;

typedef struct
{
    TIM_CR1_t CR1;          // 0x00
    uint32_t  CR2;          // 0x04
    uint32_t  SMCR;         // 0x08
    TIM_DIER_t DIER;        // 0x0C
    TIM_SR_t   SR;          // 0x10
    uint32_t  EGR;          // 0x14
    uint32_t  CCMR1;        // 0x18
    uint32_t  CCMR2;        // 0x1C
    uint32_t  CCER;         // 0x20
    uint32_t  CNT;          // 0x24
    uint32_t  PSC;          // 0x28
    uint32_t  ARR;          // 0x2C
    uint32_t  RESERVED[1];
    uint32_t  CCR1;         // 0x34
    uint32_t  CCR2;         // 0x38
    uint32_t  CCR3;         // 0x3C
    uint32_t  CCR4;         // 0x40
} TIM_t;

#define TIM2   (*(volatile TIM_t *)0x40000000)

void TIM2_Init(void);
extern _Bool tim2Flag;

#endif
