/*
 * uart.h
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#ifndef UART_H_
#define UART_H_

typedef struct {
    volatile uint32_t PE     :1;
    volatile uint32_t FE     :1;
    volatile uint32_t NF     :1;
    volatile uint32_t ORE    :1;
    volatile uint32_t IDLE   :1;
    volatile uint32_t RXNE   :1;
    volatile uint32_t TC     :1;
    volatile uint32_t TXE    :1;
    volatile uint32_t LBD    :1;
    volatile uint32_t CTS    :1;
    volatile uint32_t RESERVED:22;
} USART_SR_t;

typedef struct {
    volatile uint32_t DR :9;
    volatile uint32_t RESERVED :23;
} USART_DR_t;

typedef struct {
    volatile uint32_t DIV_Fraction :4;
    volatile uint32_t DIV_Mantissa :12;
    volatile uint32_t RESERVED     :16;
} USART_BRR_t;

typedef struct {
    volatile uint32_t SBK     :1;
    volatile uint32_t RWU     :1;
    volatile uint32_t RE      :1;
    volatile uint32_t TE      :1;
    volatile uint32_t IDLEIE  :1;
    volatile uint32_t RXNEIE  :1;
    volatile uint32_t TCIE    :1;
    volatile uint32_t TXEIE   :1;
    volatile uint32_t PEIE    :1;
    volatile uint32_t PS      :1;
    volatile uint32_t PCE     :1;
    volatile uint32_t WAKE    :1;
    volatile uint32_t M       :1;
    volatile uint32_t UE      :1;
    volatile uint32_t RESERVED:18;
} USART_CR1_t;

typedef struct {
    volatile uint32_t ADD      :4;
    volatile uint32_t LBDL     :1;
    volatile uint32_t LBDIE    :1;
    volatile uint32_t RESERVED0:1;
    volatile uint32_t LBCL     :1;
    volatile uint32_t CPHA     :1;
    volatile uint32_t CPOL     :1;
    volatile uint32_t CLKEN    :1;
    volatile uint32_t STOP     :2;
    volatile uint32_t LINEN    :1;
    volatile uint32_t RESERVED1:17;
} USART_CR2_t;

typedef struct {
    volatile uint32_t EIE      :1;
    volatile uint32_t IREN     :1;
    volatile uint32_t IRLP     :1;
    volatile uint32_t HDSEL    :1;
    volatile uint32_t NACK     :1;
    volatile uint32_t SCEN     :1;
    volatile uint32_t DMAR     :1;
    volatile uint32_t DMAT     :1;
    volatile uint32_t RTSE     :1;
    volatile uint32_t CTSE     :1;
    volatile uint32_t CTSIE    :1;
    volatile uint32_t ONEBIT   :1;
    volatile uint32_t RESERVED :20;
} USART_CR3_t;

typedef struct {
    volatile uint32_t PSC :8;
    volatile uint32_t GT  :8;
    volatile uint32_t RESERVED :16;
} USART_GTPR_t;

typedef struct {
    USART_SR_t  SR;     // Status register
    USART_DR_t  DR;     // 0x04 // Data register
    USART_BRR_t BRR;    // Baud rate register
    USART_CR1_t CR1;    // Control register 1
    USART_CR2_t CR2;    // 0x10
    USART_CR3_t CR3;    // 0x14
    USART_GTPR_t GTPR;  // Guard time and prescaler register
} USART_t;

#define USART1 (*(volatile USART_t*)0x40011000)
#define USART2 (*(volatile USART_t*)0x40004400)
#define USART3 (*(volatile USART_t*)0x40004800)
#define UART4  (*(volatile USART_t*)0x40004C00)
#define UART5  (*(volatile USART_t*)0x40005000)
#define USART6 (*(volatile USART_t*)0x40011400)

void UART2_Init(void);
char UART2_ReadChar(void);
void UART2_WriteChar(char);

typedef enum {
    UART_DISABLE = 0,
    UART_ENABLE  = 1
} UART_State_t;

typedef enum {
    UART_WORDLEN_8B = 0,
    UART_WORDLEN_9B = 1
} UART_WordLength_t;

typedef enum {
    UART_PARITY_NONE = 0,
    UART_PARITY_EVEN,
    UART_PARITY_ODD
} UART_Parity_t;

typedef enum {
    UART_STOPBITS_1 = 0,
    UART_STOPBITS_2 = 2
} UART_StopBits_t;

typedef enum {
    UART_MODE_RX = 1,
    UART_MODE_TX = 2,
    UART_MODE_TX_RX = 3
} UART_Mode_t;

#endif /* UART_H_ */
