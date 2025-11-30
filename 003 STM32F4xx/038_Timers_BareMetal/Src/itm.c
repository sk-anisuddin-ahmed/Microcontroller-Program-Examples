#include <stdint.h>

/* DEMCR register at 0xE000EDFC */
typedef struct {
    volatile uint32_t VC_CORERESET : 1;
    volatile uint32_t RESERVED0    : 3;
    volatile uint32_t VC_MMERR     : 1;
    volatile uint32_t VC_NOCPERR   : 1;
    volatile uint32_t VC_CHKERR    : 1;
    volatile uint32_t VC_STATERR   : 1;
    volatile uint32_t VC_BUSERR    : 1;
    volatile uint32_t VC_INTERR    : 1;
    volatile uint32_t VC_HARDERR   : 1;
    volatile uint32_t RESERVED1    : 5;
    volatile uint32_t MON_EN       : 1;
    volatile uint32_t MON_PEND     : 1;
    volatile uint32_t MON_STEP     : 1;
    volatile uint32_t MON_REQ      : 1;
    volatile uint32_t RESERVED2    : 4;
    volatile uint32_t TRCENA       : 1;
    volatile uint32_t RESERVED3    : 7;
} DEMCR_bits_t;
#define DEMCR (*(volatile DEMCR_bits_t*)0xE000EDFCUL)

/* ITM Trace Enable Register at 0xE0000E00 */
typedef struct {
    volatile uint32_t STIM0  : 1;
    volatile uint32_t STIM1  : 1;
    volatile uint32_t STIM2  : 1;
    volatile uint32_t STIM3  : 1;
    volatile uint32_t STIM4  : 1;
    volatile uint32_t STIM5  : 1;
    volatile uint32_t STIM6  : 1;
    volatile uint32_t STIM7  : 1;
    volatile uint32_t STIM8  : 1;
    volatile uint32_t STIM9  : 1;
    volatile uint32_t STIM10 : 1;
    volatile uint32_t STIM11 : 1;
    volatile uint32_t STIM12 : 1;
    volatile uint32_t STIM13 : 1;
    volatile uint32_t STIM14 : 1;
    volatile uint32_t STIM15 : 1;
    volatile uint32_t STIM16 : 1;
    volatile uint32_t STIM17 : 1;
    volatile uint32_t STIM18 : 1;
    volatile uint32_t STIM19 : 1;
    volatile uint32_t STIM20 : 1;
    volatile uint32_t STIM21 : 1;
    volatile uint32_t STIM22 : 1;
    volatile uint32_t STIM23 : 1;
    volatile uint32_t STIM24 : 1;
    volatile uint32_t STIM25 : 1;
    volatile uint32_t STIM26 : 1;
    volatile uint32_t STIM27 : 1;
    volatile uint32_t STIM28 : 1;
    volatile uint32_t STIM29 : 1;
    volatile uint32_t STIM30 : 1;
    volatile uint32_t STIM31 : 1;
} ITM_TER_bits_t;
#define ITM_TER (*(volatile ITM_TER_bits_t*)0xE0000E00UL)

/* ITM Stimulus Port registers at 0xE0000000 */
typedef union {
    struct {
        volatile uint32_t READY : 1;
    };

    struct {
        volatile uint32_t DATA : 8;
    };
} ITM_STIM_t;
#define ITM_STIM_PORT0 (*(volatile ITM_STIM_t*)0xE0000000UL)

void ITM_Init(void)
{
    DEMCR.TRCENA = 1;
    ITM_TER.STIM0 = 1;
}

void ITM_SendChar(uint8_t ch)
{
	while(!ITM_STIM_PORT0.READY);
    ITM_STIM_PORT0.DATA = ch;
}

int __io_putchar(int ch)
{
    ITM_SendChar((uint8_t)ch);
    return ch;
}
