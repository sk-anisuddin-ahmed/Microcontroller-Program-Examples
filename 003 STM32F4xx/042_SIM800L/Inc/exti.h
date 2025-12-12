/*
 * exti.h
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#ifndef EXTI_H_
#define EXTI_H_

typedef struct {
    volatile uint32_t MEM_MODE    :2;
    volatile uint32_t RESERVED0   :30;
} SYSCFG_MEMRMP_t;

typedef struct {
    volatile uint32_t FB_MODE     :1;
    volatile uint32_t RESERVED0   :31;
} SYSCFG_PMC_t;

typedef struct {
    volatile uint32_t EXTI0  :4;
    volatile uint32_t EXTI1  :4;
    volatile uint32_t EXTI2  :4;
    volatile uint32_t EXTI3  :4;
    volatile uint32_t RESERVED:16;
} SYSCFG_EXTICR1_t;

typedef struct {
    volatile uint32_t EXTI4  :4;
    volatile uint32_t EXTI5  :4;
    volatile uint32_t EXTI6  :4;
    volatile uint32_t EXTI7  :4;
    volatile uint32_t RESERVED:16;
} SYSCFG_EXTICR2_t;

typedef struct {
    volatile uint32_t EXTI8  :4;
    volatile uint32_t EXTI9  :4;
    volatile uint32_t EXTI10 :4;
    volatile uint32_t EXTI11 :4;
    volatile uint32_t RESERVED:16;
} SYSCFG_EXTICR3_t;

typedef struct {
    volatile uint32_t EXTI12 :4;
    volatile uint32_t EXTI13 :4;
    volatile uint32_t EXTI14 :4;
    volatile uint32_t EXTI15 :4;
    volatile uint32_t RESERVED:16;
} SYSCFG_EXTICR4_t;

typedef struct {
    volatile uint32_t CMP_PD   :1;
    volatile uint32_t RESERVED :31;
} SYSCFG_CMPCR_t;

typedef struct {
    SYSCFG_MEMRMP_t     MEMRMP;     // 0x00
    SYSCFG_PMC_t        PMC;        // 0x04
    SYSCFG_EXTICR1_t    EXTICR1;    // 0x08
    SYSCFG_EXTICR2_t    EXTICR2;    // 0x0C
    SYSCFG_EXTICR3_t    EXTICR3;    // 0x10
    SYSCFG_EXTICR4_t    EXTICR4;    // 0x14
    uint32_t            RESERVED0;  // 0x18
    SYSCFG_CMPCR_t      CMPCR;      // 0x20
} SYSCFG_t;

#define SYSCFG (*(volatile SYSCFG_t *)0x40013800)

typedef struct {
    volatile uint32_t MR0  :1;
    volatile uint32_t MR1  :1;
    volatile uint32_t MR2  :1;
    volatile uint32_t MR3  :1;
    volatile uint32_t MR4  :1;
    volatile uint32_t MR5  :1;
    volatile uint32_t MR6  :1;
    volatile uint32_t MR7  :1;
    volatile uint32_t MR8  :1;
    volatile uint32_t MR9  :1;
    volatile uint32_t MR10 :1;
    volatile uint32_t MR11 :1;
    volatile uint32_t MR12 :1;
    volatile uint32_t MR13 :1;
    volatile uint32_t MR14 :1;
    volatile uint32_t MR15 :1;
    volatile uint32_t MR16 :1;
    volatile uint32_t MR17 :1;
    volatile uint32_t MR18 :1;
    volatile uint32_t RESERVED :13;
} EXTI_IMR_t;

typedef struct {
    volatile uint32_t EM0  :1;
    volatile uint32_t EM1  :1;
    volatile uint32_t EM2  :1;
    volatile uint32_t EM3  :1;
    volatile uint32_t EM4  :1;
    volatile uint32_t EM5  :1;
    volatile uint32_t EM6  :1;
    volatile uint32_t EM7  :1;
    volatile uint32_t EM8  :1;
    volatile uint32_t EM9  :1;
    volatile uint32_t EM10 :1;
    volatile uint32_t EM11 :1;
    volatile uint32_t EM12 :1;
    volatile uint32_t EM13 :1;
    volatile uint32_t EM14 :1;
    volatile uint32_t EM15 :1;
    volatile uint32_t EM16 :1;
    volatile uint32_t EM17 :1;
    volatile uint32_t EM18 :1;
    volatile uint32_t RESERVED :13;
} EXTI_EMR_t;

typedef struct {
    volatile uint32_t TR0  :1;
    volatile uint32_t TR1  :1;
    volatile uint32_t TR2  :1;
    volatile uint32_t TR3  :1;
    volatile uint32_t TR4  :1;
    volatile uint32_t TR5  :1;
    volatile uint32_t TR6  :1;
    volatile uint32_t TR7  :1;
    volatile uint32_t TR8  :1;
    volatile uint32_t TR9  :1;
    volatile uint32_t TR10 :1;
    volatile uint32_t TR11 :1;
    volatile uint32_t TR12 :1;
    volatile uint32_t TR13 :1;
    volatile uint32_t TR14 :1;
    volatile uint32_t TR15 :1;
    volatile uint32_t TR16 :1;
    volatile uint32_t TR17 :1;
    volatile uint32_t TR18 :1;
    volatile uint32_t RESERVED :13;
} EXTI_RTSR_t;

typedef struct {
    volatile uint32_t TR0  :1;
    volatile uint32_t TR1  :1;
    volatile uint32_t TR2  :1;
    volatile uint32_t TR3  :1;
    volatile uint32_t TR4  :1;
    volatile uint32_t TR5  :1;
    volatile uint32_t TR6  :1;
    volatile uint32_t TR7  :1;
    volatile uint32_t TR8  :1;
    volatile uint32_t TR9  :1;
    volatile uint32_t TR10 :1;
    volatile uint32_t TR11 :1;
    volatile uint32_t TR12 :1;
    volatile uint32_t TR13 :1;
    volatile uint32_t TR14 :1;
    volatile uint32_t TR15 :1;
    volatile uint32_t TR16 :1;
    volatile uint32_t TR17 :1;
    volatile uint32_t TR18 :1;
    volatile uint32_t RESERVED :13;
} EXTI_FTSR_t;

typedef struct {
    volatile uint32_t SWIER0  :1;
    volatile uint32_t SWIER1  :1;
    volatile uint32_t SWIER2  :1;
    volatile uint32_t SWIER3  :1;
    volatile uint32_t SWIER4  :1;
    volatile uint32_t SWIER5  :1;
    volatile uint32_t SWIER6  :1;
    volatile uint32_t SWIER7  :1;
    volatile uint32_t SWIER8  :1;
    volatile uint32_t SWIER9  :1;
    volatile uint32_t SWIER10 :1;
    volatile uint32_t SWIER11 :1;
    volatile uint32_t SWIER12 :1;
    volatile uint32_t SWIER13 :1;
    volatile uint32_t SWIER14 :1;
    volatile uint32_t SWIER15 :1;
    volatile uint32_t SWIER16 :1;
    volatile uint32_t SWIER17 :1;
    volatile uint32_t SWIER18 :1;
    volatile uint32_t RESERVED :13;
} EXTI_SWIER_t;

typedef struct {
    volatile uint32_t PR0  :1;
    volatile uint32_t PR1  :1;
    volatile uint32_t PR2  :1;
    volatile uint32_t PR3  :1;
    volatile uint32_t PR4  :1;
    volatile uint32_t PR5  :1;
    volatile uint32_t PR6  :1;
    volatile uint32_t PR7  :1;
    volatile uint32_t PR8  :1;
    volatile uint32_t PR9  :1;
    volatile uint32_t PR10 :1;
    volatile uint32_t PR11 :1;
    volatile uint32_t PR12 :1;
    volatile uint32_t PR13 :1;
    volatile uint32_t PR14 :1;
    volatile uint32_t PR15 :1;
    volatile uint32_t PR16 :1;
    volatile uint32_t PR17 :1;
    volatile uint32_t PR18 :1;
    volatile uint32_t RESERVED :13;
} EXTI_PR_t;

typedef struct {
    EXTI_IMR_t   IMR;
    EXTI_EMR_t   EMR;
    EXTI_RTSR_t  RTSR;
    EXTI_FTSR_t  FTSR;
    EXTI_SWIER_t SWIER;
    EXTI_PR_t    PR;
} EXTI_t;

#define EXTI   (*(volatile EXTI_t *)0x40013C00)

typedef enum {
    EXTI_PORT_A = 0x0,
    EXTI_PORT_B = 0x1,
    EXTI_PORT_C = 0x2,
    EXTI_PORT_D = 0x3,
    EXTI_PORT_E = 0x4,
    EXTI_PORT_F = 0x5,
    EXTI_PORT_G = 0x6,
    EXTI_PORT_H = 0x7
} EXTI_Port_t;

typedef enum {
    EXTI_DISABLE = 0,
    EXTI_ENABLE  = 1
} EXTI_Mask_t;

typedef enum {
    EXTI_MASK_DISABLE = 0,
    EXTI_MASK_ENABLE  = 1
} EXTI_MaskState_t;

typedef enum {
    EXTI_RISING_DISABLE = 0,
    EXTI_RISING_ENABLE  = 1
} EXTI_RisingState_t;

typedef enum {
    EXTI_FALLING_DISABLE = 0,
    EXTI_FALLING_ENABLE  = 1
} EXTI_FallingState_t;

#endif /* EXTI_H_ */
