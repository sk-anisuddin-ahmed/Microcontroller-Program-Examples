/*
 * adc.h
 *
 *  Created on: 30-Nov-2025
 *      Author: skani
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef struct {
    volatile uint32_t AWD  :1;   // Analog watchdog flag
    volatile uint32_t EOC  :1;   // End of conversion
    volatile uint32_t JEOC :1;   // Injected end of conversion
    volatile uint32_t JSTRT:1;   // Injected start flag
    volatile uint32_t STRT :1;   // Regular channel start flag
    volatile uint32_t OVR  :1;   // Overrun
    volatile uint32_t RESERVED:26;
} ADC_SR_t;

typedef struct {
    volatile uint32_t AWDCH :5;   // Analog watchdog channel
    volatile uint32_t EOCIE :1;   // Interrupt enable EOC
    volatile uint32_t AWDIE :1;   // Interrupt enable AWD
    volatile uint32_t JEOCIE:1;   // Interrupt enable JEOC
    volatile uint32_t SCAN  :1;   // Scan mode
    volatile uint32_t AWDSGL:1;   // Enable watchdog on single channel
    volatile uint32_t JAUTO :1;   // Auto injected conversions
    volatile uint32_t DISCEN:1;   // Discontinuous mode
    volatile uint32_t JDISCEN:1;  // Injected discontinuous mode
    volatile uint32_t DISCNUM:3;  // Number of conversions
    volatile uint32_t RESERVED0:6;
    volatile uint32_t JAWDEN :1;
    volatile uint32_t AWDEN  :1;
    volatile uint32_t RESERVED1:8;
} ADC_CR1_t;

typedef struct {
    volatile uint32_t ADON     :1; // ADC ON/off
    volatile uint32_t CONT     :1; // Continuous mode
    volatile uint32_t RESERVED0:6;
    volatile uint32_t DMA      :1; // DMA enable
    volatile uint32_t DDS      :1; // DMA disable selection
    volatile uint32_t EOCS     :1; // End of conversion selection
    volatile uint32_t ALIGN    :1; // Data alignment
    volatile uint32_t RESERVED1:4;
    volatile uint32_t JEXTSEL  :4;
    volatile uint32_t JEXTEN   :2;
    volatile uint32_t JSWSTART :1;
    volatile uint32_t RESERVED2:1;
    volatile uint32_t EXTSEL   :4;
    volatile uint32_t EXTEN    :2;
    volatile uint32_t SWSTART  :1; // Software start
    volatile uint32_t RESERVED3:1;
} ADC_CR2_t;

typedef struct {
    volatile uint32_t SMP0 :3;
    volatile uint32_t SMP1 :3;
    volatile uint32_t SMP2 :3;
    volatile uint32_t SMP3 :3;
    volatile uint32_t SMP4 :3;
    volatile uint32_t SMP5 :3;
    volatile uint32_t SMP6 :3;
    volatile uint32_t SMP7 :3;
    volatile uint32_t SMP8 :3;
    volatile uint32_t SMP9 :3;
} ADC_SMPR2_t;

typedef struct {
    volatile uint32_t SQ1 :5;
    volatile uint32_t SQ2 :5;
    volatile uint32_t SQ3 :5;
    volatile uint32_t SQ4 :5;
    volatile uint32_t SQ5 :5;
    volatile uint32_t SQ6 :5;
    volatile uint32_t RESERVED:2;
} ADC_SQR3_t;

typedef struct {
    volatile uint32_t DATA :16;
    volatile uint32_t RESERVED:16;
} ADC_DR_t;

typedef struct {
    ADC_SR_t   SR;      // 0x00
    ADC_CR1_t  CR1;     // 0x04
    ADC_CR2_t  CR2;     // 0x08
    uint32_t   SMPR1;   // 0x0C
    ADC_SMPR2_t SMPR2;  // 0x10
    uint32_t   JOFR1;
    uint32_t   JOFR2;
    uint32_t   JOFR3;
    uint32_t   JOFR4;
    uint32_t   HTR;
    uint32_t   LTR;
    uint32_t   SQR1;
    uint32_t   SQR2;
    ADC_SQR3_t SQR3;    // 0x34
    uint32_t   JSQR;
    uint32_t   JDR1;
    uint32_t   JDR2;
    uint32_t   JDR3;
    uint32_t   JDR4;
    ADC_DR_t   DR;      // 0x4C
} ADC_t;

#define ADC1 (*(volatile ADC_t*)0x40012000)

typedef enum {
    ADC_SAMPLE_3CYC   = 0,
    ADC_SAMPLE_15CYC  = 1,
    ADC_SAMPLE_28CYC  = 2,
    ADC_SAMPLE_56CYC  = 3,
    ADC_SAMPLE_84CYC  = 4,
    ADC_SAMPLE_112CYC = 5,
    ADC_SAMPLE_144CYC = 6,
    ADC_SAMPLE_480CYC = 7
} ADC_SampleTime_t;

void ADC1_Init(void);
uint16_t ADC1_Read(void);

#endif /* ADC_H_ */
