/*
 * gpio.h
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>

typedef struct {
    volatile uint32_t PIN0  :2;
    volatile uint32_t PIN1  :2;
    volatile uint32_t PIN2  :2;
    volatile uint32_t PIN3  :2;
    volatile uint32_t PIN4  :2;
    volatile uint32_t PIN5  :2;
    volatile uint32_t PIN6  :2;
    volatile uint32_t PIN7  :2;
    volatile uint32_t PIN8  :2;
    volatile uint32_t PIN9  :2;
    volatile uint32_t PIN10 :2;
    volatile uint32_t PIN11 :2;
    volatile uint32_t PIN12 :2;
    volatile uint32_t PIN13 :2;
    volatile uint32_t PIN14 :2;
    volatile uint32_t PIN15 :2;
} MODER_t;

typedef struct {
    volatile uint32_t PIN0  :1;
    volatile uint32_t PIN1  :1;
    volatile uint32_t PIN2  :1;
    volatile uint32_t PIN3  :1;
    volatile uint32_t PIN4  :1;
    volatile uint32_t PIN5  :1;
    volatile uint32_t PIN6  :1;
    volatile uint32_t PIN7  :1;
    volatile uint32_t PIN8  :1;
    volatile uint32_t PIN9  :1;
    volatile uint32_t PIN10 :1;
    volatile uint32_t PIN11 :1;
    volatile uint32_t PIN12 :1;
    volatile uint32_t PIN13 :1;
    volatile uint32_t PIN14 :1;
    volatile uint32_t PIN15 :1;
    volatile uint32_t RESERVED :16;
} OTYPER_t;

typedef struct {
    volatile uint32_t PIN0  :2;
    volatile uint32_t PIN1  :2;
    volatile uint32_t PIN2  :2;
    volatile uint32_t PIN3  :2;
    volatile uint32_t PIN4  :2;
    volatile uint32_t PIN5  :2;
    volatile uint32_t PIN6  :2;
    volatile uint32_t PIN7  :2;
    volatile uint32_t PIN8  :2;
    volatile uint32_t PIN9  :2;
    volatile uint32_t PIN10 :2;
    volatile uint32_t PIN11 :2;
    volatile uint32_t PIN12 :2;
    volatile uint32_t PIN13 :2;
    volatile uint32_t PIN14 :2;
    volatile uint32_t PIN15 :2;
} OSPEEDR_t;

typedef struct {
    volatile uint32_t PIN0  :2;
    volatile uint32_t PIN1  :2;
    volatile uint32_t PIN2  :2;
    volatile uint32_t PIN3  :2;
    volatile uint32_t PIN4  :2;
    volatile uint32_t PIN5  :2;
    volatile uint32_t PIN6  :2;
    volatile uint32_t PIN7  :2;
    volatile uint32_t PIN8  :2;
    volatile uint32_t PIN9  :2;
    volatile uint32_t PIN10 :2;
    volatile uint32_t PIN11 :2;
    volatile uint32_t PIN12 :2;
    volatile uint32_t PIN13 :2;
    volatile uint32_t PIN14 :2;
    volatile uint32_t PIN15 :2;
} PUPDR_t;

typedef struct {
    volatile uint32_t PIN0  :1;
    volatile uint32_t PIN1  :1;
    volatile uint32_t PIN2  :1;
    volatile uint32_t PIN3  :1;
    volatile uint32_t PIN4  :1;
    volatile uint32_t PIN5  :1;
    volatile uint32_t PIN6  :1;
    volatile uint32_t PIN7  :1;
    volatile uint32_t PIN8  :1;
    volatile uint32_t PIN9  :1;
    volatile uint32_t PIN10 :1;
    volatile uint32_t PIN11 :1;
    volatile uint32_t PIN12 :1;
    volatile uint32_t PIN13 :1;
    volatile uint32_t PIN14 :1;
    volatile uint32_t PIN15 :1;
    volatile uint32_t RESERVED :16;
} IDR_t;

typedef struct {
    volatile uint32_t PIN0  :1;
    volatile uint32_t PIN1  :1;
    volatile uint32_t PIN2  :1;
    volatile uint32_t PIN3  :1;
    volatile uint32_t PIN4  :1;
    volatile uint32_t PIN5  :1;
    volatile uint32_t PIN6  :1;
    volatile uint32_t PIN7  :1;
    volatile uint32_t PIN8  :1;
    volatile uint32_t PIN9  :1;
    volatile uint32_t PIN10 :1;
    volatile uint32_t PIN11 :1;
    volatile uint32_t PIN12 :1;
    volatile uint32_t PIN13 :1;
    volatile uint32_t PIN14 :1;
    volatile uint32_t PIN15 :1;
    volatile uint32_t RESERVED :16;
} ODR_t;

typedef struct {
    MODER_t   MODER;      // 0x00
    OTYPER_t  OTYPER;     // 0x04
    OSPEEDR_t OSPEEDR;    // 0x08
    PUPDR_t   PUPDR;      // 0x0C
    IDR_t     IDR;        // 0x10
    ODR_t     ODR;        // 0x14
} GPIO_t;

#define GPIOA (*(volatile GPIO_t *)0x40020000)
#define GPIOB (*(volatile GPIO_t *)0x40020400)
#define GPIOC (*(volatile GPIO_t *)0x40020800)
#define GPIOD (*(volatile GPIO_t *)0x40020C00)
#define GPIOE (*(volatile GPIO_t *)0x40021000)
#define GPIOF (*(volatile GPIO_t *)0x40021400)
#define GPIOG (*(volatile GPIO_t *)0x40021800)
#define GPIOH (*(volatile GPIO_t *)0x40021C00)
#define GPIOI (*(volatile GPIO_t *)0x40022000)

typedef enum {
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_AF     = 0x2,
    GPIO_MODE_ANALOG = 0x3
} GPIO_Mode_t;

typedef enum {
    GPIO_OTYPE_PP = 0,
    GPIO_OTYPE_OD = 1
} GPIO_OType_t;

typedef enum {
    GPIO_SPEED_LOW    = 0,
    GPIO_SPEED_MEDIUM = 1,
    GPIO_SPEED_FAST   = 2,
    GPIO_SPEED_HIGH   = 3
} GPIO_Speed_t;

typedef enum {
    GPIO_NOPULL  = 0,
    GPIO_PULLUP  = 1,
    GPIO_PULLDOWN= 2
} GPIO_Pull_t;

typedef enum {
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET   = 1
} GPIO_PinState_t;

typedef enum {
    GPIO_PIN_LOW  = 0,
    GPIO_PIN_HIGH = 1
} GPIO_PinInput_t;

void GPIO_Init(void);
void Button_Init(void);

#endif /* GPIO_H_ */
