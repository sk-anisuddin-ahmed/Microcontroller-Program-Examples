/*
 * dma.h
 *
 *  Created on: 28-Nov-2025
 *      Author: skani
 */

#ifndef DMA_H_
#define DMA_H_

typedef struct
{
	volatile uint32_t EN :1; // Bit 0  - Stream enable
	volatile uint32_t DMEIE :1; // Bit 1  - Direct mode error interrupt enable
	volatile uint32_t TEIE :1; // Bit 2  - Transfer error interrupt enable
	volatile uint32_t HTIE :1; // Bit 3  - Half-transfer interrupt enable
	volatile uint32_t TCIE :1; // Bit 4  - Transfer complete interrupt enable
	volatile uint32_t PFCTRL :1; // Bit 5  - Peripheral flow controller
	volatile uint32_t DIR :2; // Bits 6–7 DIR[1:0]
	volatile uint32_t CIRC :1; // Bit 8  - Circular mode
	volatile uint32_t PINC :1; // Bit 9  - Peripheral increment
	volatile uint32_t MINC :1; // Bit 10 - Memory increment
	volatile uint32_t PSIZE :2; // Bits 11–12 - Peripheral size
	volatile uint32_t MSIZE :2; // Bits 13–14 - Memory size
	volatile uint32_t PINCOS :1; // Bit 15 - Peripheral increment offset
	volatile uint32_t PL :2; // Bits 16–17 Priority level
	volatile uint32_t DBM :1; // Bit 18 - Double buffer mode
	volatile uint32_t CT :1; // Bit 19 - Current target (double buffer)
	volatile uint32_t RESERVED0 :1; // Bit 20
	volatile uint32_t PBURST :2; // Bits 21–22 Peripheral burst
	volatile uint32_t MBURST :2; // Bits 23–24 Memory burst
	volatile uint32_t CHSEL :3; // Bits 25–27 Channel select
	volatile uint32_t RESERVED1 :4; // Bits 28–31
} DMA_SxCR_t;

typedef struct
{
	volatile uint32_t FTH :2; // FIFO threshold
	volatile uint32_t DMDIS :1; // Direct mode disable
	volatile uint32_t FS :3; // FIFO status
	volatile uint32_t RESERVED0 :1;
	volatile uint32_t FEIE :1; // FIFO error interrupt enable
	volatile uint32_t RESERVED1 :24;
} DMA_SxFCR_t;

typedef struct
{
	DMA_SxCR_t CR;
	volatile uint32_t NDTR;
	volatile uint32_t PAR;
	volatile uint32_t M0AR;
	volatile uint32_t M1AR;
	DMA_SxFCR_t FCR;
} DMA_Stream_t;

typedef struct
{
	volatile uint32_t FEIF0    :1;  // Bit 0  - FIFO error flag Stream4
	volatile uint32_t RESERVED0:1;  // Bit 1  - Reserved
	volatile uint32_t DMEIF0   :1;  // Bit 2  - Direct mode error flag Stream4
	volatile uint32_t TEIF0    :1;  // Bit 3  - Transfer error flag Stream4
	volatile uint32_t HTIF0    :1;  // Bit 4  - Half transfer flag Stream4
	volatile uint32_t TCIF0    :1;  // Bit 5  - Transfer complete flag Stream4
	volatile uint32_t FEIF1    :1;  // Bit 8  - FIFO error flag Stream5
	volatile uint32_t RESERVED1:1;  // Bit 9  - Reserved
	volatile uint32_t DMEIF1   :1;  // Bit 10 - Direct mode error flag Stream5
	volatile uint32_t TEIF1    :1;  // Bit 11 - Transfer error flag Stream5
	volatile uint32_t HTIF1    :1;  // Bit 12 - Half transfer flag Stream5
	volatile uint32_t TCIF1    :1;  // Bit 13 - Transfer complete flag Stream5
	volatile uint32_t RESERVED2:4;  // Bits 12–15 Reserved
	volatile uint32_t FEIF2    :1;  // Bit 16 - FIFO error flag Stream6
	volatile uint32_t RESERVED3:1;  // Bit 17 - Reserved
	volatile uint32_t DMEIF2   :1;  // Bit 18 - Direct mode error flag Stream6
	volatile uint32_t TEIF2    :1;  // Bit 19 - Transfer error flag Stream6
	volatile uint32_t HTIF2    :1;  // Bit 20 - Half transfer flag Stream6
	volatile uint32_t TCIF2    :1;  // Bit 21 - Transfer complete flag Stream6
	volatile uint32_t FEIF3    :1;  // Bit 24 - FIFO error flag Stream7
	volatile uint32_t RESERVED4:1;  // Bits 22–23 Reserved
	volatile uint32_t DMEIF3   :1;  // Bit 26 - Direct mode error flag Stream7
	volatile uint32_t TEIF3    :1;  // Bit 27 - Transfer error flag Stream7
	volatile uint32_t HTIF3    :1;  // Bit 28 - Half transfer flag Stream7
	volatile uint32_t TCIF3    :1;  // Bit 29 - Transfer complete flag Stream7
	volatile uint32_t RESERVED7:4;  // Bits 28–31 Reserved
} DMA_LISR_t;

typedef struct
{
    volatile uint32_t FEIF4    :1;  // Bit 0  - FIFO error flag Stream4
    volatile uint32_t RESERVED0:1;  // Bit 1  - Reserved
    volatile uint32_t DMEIF4   :1;  // Bit 2  - Direct mode error flag Stream4
    volatile uint32_t TEIF4    :1;  // Bit 3  - Transfer error flag Stream4
    volatile uint32_t HTIF4    :1;  // Bit 4  - Half transfer flag Stream4
    volatile uint32_t TCIF4    :1;  // Bit 5  - Transfer complete flag Stream4
    volatile uint32_t FEIF5    :1;  // Bit 8  - FIFO error flag Stream5
    volatile uint32_t RESERVED1:1;  // Bit 9  - Reserved
    volatile uint32_t DMEIF5   :1;  // Bit 10 - Direct mode error flag Stream5
    volatile uint32_t TEIF5    :1;  // Bit 11 - Transfer error flag Stream5
    volatile uint32_t HTIF5    :1;  // Bit 12 - Half transfer flag Stream5
    volatile uint32_t TCIF5    :1;  // Bit 13 - Transfer complete flag Stream5
    volatile uint32_t RESERVED2:4;  // Bits 12–15 Reserved
    volatile uint32_t FEIF6    :1;  // Bit 16 - FIFO error flag Stream6
    volatile uint32_t RESERVED3:1;  // Bit 17 - Reserved
    volatile uint32_t DMEIF6   :1;  // Bit 18 - Direct mode error flag Stream6
    volatile uint32_t TEIF6    :1;  // Bit 19 - Transfer error flag Stream6
    volatile uint32_t HTIF6    :1;  // Bit 20 - Half transfer flag Stream6
    volatile uint32_t TCIF6    :1;  // Bit 21 - Transfer complete flag Stream6
    volatile uint32_t FEIF7    :1;  // Bit 24 - FIFO error flag Stream7
    volatile uint32_t RESERVED4:1;  // Bits 22–23 Reserved
    volatile uint32_t DMEIF7   :1;  // Bit 26 - Direct mode error flag Stream7
    volatile uint32_t TEIF7    :1;  // Bit 27 - Transfer error flag Stream7
    volatile uint32_t HTIF7    :1;  // Bit 28 - Half transfer flag Stream7
    volatile uint32_t TCIF7    :1;  // Bit 29 - Transfer complete flag Stream7
    volatile uint32_t RESERVED7:4;  // Bits 28–31 Reserved
} DMA_HISR_t;

typedef struct
{
	DMA_LISR_t LISR;
	DMA_HISR_t HISR;
	DMA_LISR_t LIFCR;
	DMA_HISR_t HIFCR;
	DMA_Stream_t STREAM0;
	DMA_Stream_t STREAM1;
	DMA_Stream_t STREAM2;
	DMA_Stream_t STREAM3;
	DMA_Stream_t STREAM4;
	DMA_Stream_t STREAM5;
	DMA_Stream_t STREAM6;
	DMA_Stream_t STREAM7;
} DMA_t;

#define DMA1  (*(volatile DMA_t *)0x40026000)
#define DMA2  (*(volatile DMA_t *)0x40026400)

typedef enum
{
	DMA_DIR_PERIPH_TO_MEM = 0x0,
	DMA_DIR_MEM_TO_PERIPH = 0x1,
	DMA_DIR_MEM_TO_MEM = 0x2
} DMA_Direction_t;

typedef enum
{
	DMA_CH0 = 0,
	DMA_CH1 = 1,
	DMA_CH2 = 2,
	DMA_CH3 = 3,
	DMA_CH4 = 4, // USART2 RX/TX uses Channel 4
	DMA_CH5 = 5,
	DMA_CH6 = 6,
	DMA_CH7 = 7
} DMA_Channel_t;

typedef enum
{
	DMA_DISABLE = 0,
	DMA_ENABLE = 1
} DMA_State_t;

typedef enum
{
	DMA_PRIORITY_LOW = 0,
	DMA_PRIORITY_MEDIUM = 1,
	DMA_PRIORITY_HIGH = 2,
	DMA_PRIORITY_VERYHIGH = 3
} DMA_Priority_t;

typedef enum
{
	DMA_MEM_INC_DISABLE = 0,
	DMA_MEM_INC_ENABLE = 1
} DMA_MemoryIncrement_t;

#endif /* DMA_H_ */
