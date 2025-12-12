/*
 * rcc.h
 * Created on: 27-Nov-2025
 * Author: skani
 */

#ifndef RCC_H_
#define RCC_H_

#include <stdint.h>

typedef struct
{
    volatile uint32_t GPIOAEN     : 1;   // Bit 0
    volatile uint32_t GPIOBEN     : 1;   // Bit 1
    volatile uint32_t GPIOCEN     : 1;   // Bit 2
    volatile uint32_t GPIODEN     : 1;   // Bit 3
    volatile uint32_t GPIOEEN     : 1;   // Bit 4
    volatile uint32_t GPIOFEN     : 1;   // Bit 5
    volatile uint32_t GPIOGEN     : 1;   // Bit 6
    volatile uint32_t GPIOHEN     : 1;   // Bit 7
    volatile uint32_t GPIOIEN     : 1;   // Bit 8
    volatile uint32_t RESERVED0   : 3;   // Bits 9–11 (reserved)
    volatile uint32_t CRCEN       : 1;   // Bit 12 — CRC clock enable
    volatile uint32_t RESERVED1   : 5;   // Bits 13–17
    volatile uint32_t BKPSRAMEN   : 1;   // Bit 18 — Backup SRAM enable
    volatile uint32_t RESERVED2   : 1;   // Bit 19
    volatile uint32_t CCMDATARAMEN: 1;   // Bit 20 — CCM data RAM enable
    volatile uint32_t DMA1EN      : 1;   // Bit 21 — DMA1 clock enable
    volatile uint32_t DMA2EN      : 1;   // Bit 22 — DMA2 clock enable
    volatile uint32_t RESERVED3   : 1;   // Bit 23
    volatile uint32_t ETHMACEN    : 1;   // Bit 24 — Ethernet MAC clock
    volatile uint32_t ETHMACTXEN  : 1;   // Bit 25 — Ethernet MAC Tx
    volatile uint32_t ETHMACRXEN  : 1;   // Bit 26 — Ethernet MAC Rx
    volatile uint32_t ETHMACPTPEN : 1;   // Bit 27 — Ethernet PTP
    volatile uint32_t OTGHSEN     : 1;   // Bit 28 — USB OTG HS
    volatile uint32_t OTGHSULPIEN : 1;   // Bit 29 — USB OTG HS ULPI
    volatile uint32_t RESERVED4   : 2;   // Bits 30–31
} RCC_AHB1ENR_t;

typedef struct {
    volatile uint32_t RESERVED0 :7;
    volatile uint32_t OTGFSEN   :1;
    volatile uint32_t RESERVED1 :24;
} RCC_AHB2ENR_t;

typedef struct {
    volatile uint32_t FSMCEN   :1;
    volatile uint32_t RESERVED :31;
} RCC_AHB3ENR_t;

typedef struct
{
    volatile uint32_t TIM2EN     :1;
    volatile uint32_t TIM3EN     :1;
    volatile uint32_t TIM4EN     :1;
    volatile uint32_t TIM5EN     :1;
    volatile uint32_t TIM6EN     :1;
    volatile uint32_t TIM7EN     :1;
    volatile uint32_t TIM12EN    :1;
    volatile uint32_t TIM13EN    :1;
    volatile uint32_t TIM14EN    :1;
    volatile uint32_t RESERVED0  :2;
    volatile uint32_t WWDGEN     :1;
    volatile uint32_t RESERVED1  :2;
    volatile uint32_t SPI2EN     :1;
    volatile uint32_t SPI3EN     :1;
    volatile uint32_t RESERVED2  :1;
    volatile uint32_t USART2EN   :1;
    volatile uint32_t USART3EN   :1;
    volatile uint32_t UART4EN    :1;
    volatile uint32_t UART5EN    :1;
    volatile uint32_t I2C1EN     :1;
    volatile uint32_t I2C2EN     :1;
    volatile uint32_t I2C3EN     :1;
    volatile uint32_t RESERVED3  :1;
    volatile uint32_t CAN1EN     :1;
    volatile uint32_t CAN2EN     :1;
    volatile uint32_t RESERVED4  :1;
    volatile uint32_t PWREN      :1;
    volatile uint32_t DACEN      :1;
    volatile uint32_t UART7EN    :1;
    volatile uint32_t UART8EN    :1;
} RCC_APB1ENR_t;

typedef struct {
    volatile uint32_t TIM1EN    :1;
    volatile uint32_t TIM8EN    :1;
    volatile uint32_t USART1EN  :1;
    volatile uint32_t USART2EN  :1;
    volatile uint32_t USART3EN  :1;
    volatile uint32_t USART4EN  :1;
    volatile uint32_t USART5EN  :1;
    volatile uint32_t USART6EN  :1;
    volatile uint32_t ADC1EN    :1;
    volatile uint32_t ADC2EN    :1;
    volatile uint32_t ADC3EN    :1;
    volatile uint32_t SDIOEN    :1;
    volatile uint32_t SPI1EN    :1;
    volatile uint32_t SYSCFGEN  :1;
    volatile uint32_t TIM9EN    :1;
    volatile uint32_t TIM10EN   :1;
    volatile uint32_t TIM11EN   :1;
    volatile uint32_t RESERVED  :19;
} RCC_APB2ENR_t;

typedef struct {
    volatile uint32_t CR;            // 0x00
    volatile uint32_t PLLCFGR;       // 0x04
    volatile uint32_t CFGR;          // 0x08
    volatile uint32_t CIR;           // 0x0C
    volatile uint32_t AHB1RSTR;      // 0x10
    volatile uint32_t AHB2RSTR;      // 0x14
    volatile uint32_t AHB3RSTR;      // 0x18
    uint32_t RESERVED0;              // 0x1C
    volatile uint32_t APB1RSTR;      // 0x20
    volatile uint32_t APB2RSTR;      // 0x24
    uint32_t RESERVED1[2];           // 0x28–0x2C

    RCC_AHB1ENR_t AHB1ENR;           // 0x30
    RCC_AHB2ENR_t AHB2ENR;       	 // 0x34
    RCC_AHB3ENR_t AHB3ENR;       	 // 0x38
    uint32_t RESERVED2;              // 0x3C

    RCC_APB1ENR_t APB1ENR;           // 0x40
    RCC_APB2ENR_t APB2ENR;           // 0x44
} RCC_t;

#define RCC (*(volatile RCC_t *)0x40023800)

typedef enum {
	SYSCFGEN_DISABLE = 0,
	SYSCFGEN_ENABLE  = 1
} SYSCFGEN_Enable_t;

typedef enum {
    RCC_AHB_DIV1   = 0x0,
    RCC_AHB_DIV2   = 0x8,
    RCC_AHB_DIV4   = 0x9,
    RCC_AHB_DIV8   = 0xA,
    RCC_AHB_DIV16  = 0xB,
    RCC_AHB_DIV64  = 0xC,
    RCC_AHB_DIV128 = 0xD,
    RCC_AHB_DIV256 = 0xE,
    RCC_AHB_DIV512 = 0xF
} RCC_AHBPrescaler_t;

typedef enum {
    RCC_APB1_DIV1  = 0x0,
    RCC_APB1_DIV2  = 0x4,
    RCC_APB1_DIV4  = 0x5,
    RCC_APB1_DIV8  = 0x6,
    RCC_APB1_DIV16 = 0x7
} RCC_APB1Prescaler_t;

typedef enum {
    RCC_APB2_DIV1  = 0x0,
    RCC_APB2_DIV2  = 0x4,
    RCC_APB2_DIV4  = 0x5,
    RCC_APB2_DIV8  = 0x6,
    RCC_APB2_DIV16 = 0x7
} RCC_APB2Prescaler_t;

typedef enum {
    RCC_DISABLE = 0,
    RCC_ENABLE  = 1
} RCC_Enable_t;

#endif /* RCC_H_ */
