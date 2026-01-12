/*
 * spi.h
 *
 *  Created on: 30-Nov-2025
 *      Author: skani
 */

#ifndef SPI_H_
#define SPI_H_

typedef struct {
    volatile uint32_t CPHA     :1;  // Clock phase
    volatile uint32_t CPOL     :1;  // Clock polarity
    volatile uint32_t MSTR     :1;  // Master selection
    volatile uint32_t BR       :3;  // Baud rate control
    volatile uint32_t SPE      :1;  // SPI enable
    volatile uint32_t LSBFIRST :1;  // Frame format
    volatile uint32_t SSI      :1;  // Internal slave select
    volatile uint32_t SSM      :1;  // Software slave management
    volatile uint32_t RXONLY   :1;  // Receive only
    volatile uint32_t DFF      :1;  // Data frame format
    volatile uint32_t CRCNEXT  :1;  // CRC transfer next
    volatile uint32_t CRCEN    :1;  // CRC enable
    volatile uint32_t BIDIOE   :1;  // Output enable in bidirectional mode
    volatile uint32_t BIDIMODE :1;  // Bidirectional data mode enable
    volatile uint32_t RESERVED :16;
} SPI_CR1_t;

typedef struct {
    volatile uint32_t RXDMAEN  :1;  // Rx buffer DMA enable
    volatile uint32_t TXDMAEN  :1;  // Tx buffer DMA enable
    volatile uint32_t SSOE     :1;  // SS output enable
    volatile uint32_t RESERVED0:2;
    volatile uint32_t ERRIE    :1;  // Error interrupt enable
    volatile uint32_t RXNEIE   :1;  // RX buffer not empty interrupt enable
    volatile uint32_t TXEIE    :1;  // Tx buffer empty interrupt enable
    volatile uint32_t RESERVED1:24;
} SPI_CR2_t;

typedef struct {
    volatile uint32_t RXNE     :1;  // Receive buffer not empty
    volatile uint32_t TXE      :1;  // Transmit buffer empty
    volatile uint32_t CHSIDE   :1;  // Channel side
    volatile uint32_t UDR      :1;  // Under-run flag
    volatile uint32_t CRCERR   :1;  // CRC error flag
    volatile uint32_t MODF     :1;  // Mode fault
    volatile uint32_t OVR      :1;  // Overrun flag
    volatile uint32_t BSY      :1;  // Busy flag
    volatile uint32_t FRE      :1;  // Frame format error
    volatile uint32_t RESERVED :23;
} SPI_SR_t;

typedef struct {
    volatile uint32_t DR       :16; // Data register
    volatile uint32_t RESERVED :16;
} SPI_DR_t;

typedef struct {
    volatile uint32_t CRCPOLY  :16; // CRC polynomial
    volatile uint32_t RESERVED :16;
} SPI_CRCPR_t;

typedef struct {
    volatile uint32_t RXCRC    :16; // Rx CRC
    volatile uint32_t RESERVED :16;
} SPI_RXCRCR_t;

typedef struct {
    volatile uint32_t TXCRC    :16; // Tx CRC
    volatile uint32_t RESERVED :16;
} SPI_TXCRCR_t;

typedef struct {
    volatile uint32_t CHLEN    :1;  // Channel length
    volatile uint32_t DATLEN   :2;  // Data length
    volatile uint32_t CKPOL    :1;  // Clock polarity
    volatile uint32_t I2SSTD   :2;  // I2S standard selection
    volatile uint32_t RESERVED0:1;
    volatile uint32_t PCMSYNC  :1;  // PCM frame sync
    volatile uint32_t I2SCFG   :2;  // I2S configuration mode
    volatile uint32_t I2SE     :1;  // I2S enable
    volatile uint32_t I2SMOD   :1;  // I2S mode selection
    volatile uint32_t RESERVED1:20;
} SPI_I2SCFGR_t;

typedef struct {
    volatile uint32_t I2SDIV   :8;  // I2S linear prescaler
    volatile uint32_t ODD      :1;  // Odd factor
    volatile uint32_t MCKOE    :1;  // Master clock output enable
    volatile uint32_t RESERVED :22;
} SPI_I2SPR_t;

typedef struct {
    SPI_CR1_t     CR1;       // 0x00
    SPI_CR2_t     CR2;       // 0x04
    SPI_SR_t      SR;        // 0x08
    SPI_DR_t      DR;        // 0x0C
    SPI_CRCPR_t   CRCPR;     // 0x10
    SPI_RXCRCR_t  RXCRCR;    // 0x14
    SPI_TXCRCR_t  TXCRCR;    // 0x18
    SPI_I2SCFGR_t I2SCFGR;   // 0x1C
    SPI_I2SPR_t   I2SPR;     // 0x20
} SPI_t;

/* Base addresses */
#define SPI1 (*(volatile SPI_t*)0x40013000)
#define SPI2 (*(volatile SPI_t*)0x40003800)
#define SPI3 (*(volatile SPI_t*)0x40003C00)

void SPI1_Init(void);
void SPI1_Send(uint8_t);

extern uint8_t rxSPI;

#endif /* SPI_H_ */
