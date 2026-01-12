/*
 * flash.h
 *
 *  Created on: 14-Dec-2025
 *      Author: skani
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>

/* 					  User Flash Sectors
 -------------------------------------------------------------
 Sector 0	 | 0x0800 0000 - 0x0800 3FFF | 16  Kbytes
 Sector 1    | 0x0800 4000 - 0x0800 7FFF | 16  Kbytes
 Sector 2    | 0x0800 8000 - 0x0800 BFFF | 16  Kbytes
 Sector 3    | 0x0800 C000 - 0x0800 FFFF | 16  Kbytes
 Sector 4    | 0x0801 0000 - 0x0801 FFFF | 64  Kbytes
 Sector 5    | 0x0802 0000 - 0x0803 FFFF | 128 Kbytes
 Sector 6    | 0x0804 0000 - 0x0805 FFFF | 128 Kbytes
 Sector 7    | 0x0806 0000 - 0x0807 FFFF | 128 Kbytes
 Sector 8    | 0x0808 0000 - 0x0809 FFFF | 128 Kbytes
 Sector 9    | 0x080A 0000 - 0x080B FFFF | 128 Kbytes
 Sector 10   | 0x080C 0000 - 0x080D FFFF | 128 Kbytes
 Sector 11   | 0x080E 0000 - 0x080F FFFF | 128 Kbytes
 */

typedef struct
{
	volatile uint32_t LATENCY :4;   // bits 0–3 Latency (F405/407)
	volatile uint32_t RESERVED1 :4; // bits 4–7
	volatile uint32_t PRFTEN :1;   	// bit 8 Prefetch enable
	volatile uint32_t ICEN :1;   	// bit 9 Instruction cache enable
	volatile uint32_t DCEN :1;   	// bit 10 Data cache enable
	volatile uint32_t ICRST :1;   	// bit 11 Instruction cache reset
	volatile uint32_t DCRST :1;   	// bit 12 Data cache reset
	volatile uint32_t RESERVED2 :19;// bits 13–31
} ACR_Bits;

typedef struct
{
	volatile uint32_t KEY :32;      // bits 0–31 Key value
} KEYR_Bits;

typedef struct
{
	volatile uint32_t OPTKEY :32;   // bits 0–31 Option key value
} OPTKEYR_Bits;

typedef struct
{
	volatile uint32_t EOP :1;   	// bit 0 End of operation
	volatile uint32_t OPERR :1;  	// bit 1 Operation error
	volatile uint32_t RESERVED :2;  // bit 2
	volatile uint32_t WRPERR :1;   	// bit 4 Write protection error
	volatile uint32_t PGAERR :1;   	// bit 5 Programming alignment error
	volatile uint32_t PGPERR :1;   	// bit 6 Programming parallelism error
	volatile uint32_t PGSERR :1;   	// bit 7 Programming sequence error
	volatile uint32_t RDERR :1;		// Proprietary readout protection (PCROP) error
	volatile uint32_t RESERVED3 :7; // bits 9–15
	volatile uint32_t BSY :1;   	// bit 16 Busy
	volatile uint32_t RESERVED4 :15;// bits 17–31
} SR_Bits;

typedef struct
{
	volatile uint32_t PG :1;   		// bit 0 Programming
	volatile uint32_t SER :1;   	// bit 1 Sector erase
	volatile uint32_t MER :1;   	// bit 2 Mass erase
	volatile uint32_t SNB :5;   	// bits 3–7 Sector number
	volatile uint32_t PSIZE :2;   	// bits 8–9 Program size
	volatile uint32_t RESERVED3 :5; // bits 10–14
	volatile uint32_t MER1 :1;   	// bit 15
	volatile uint32_t STRT :1;   	// bit 16 Start
	volatile uint32_t RESERVED4 :7; // bits 17–23
	volatile uint32_t EOPIE :1;   	// bit 24 End of operation interrupt enable
	volatile uint32_t ERRIE :1;  	// bit 25 Error interrupt enable
	volatile uint32_t RESERVED5 :5; // bits 26–30
	volatile uint32_t LOCK :1;   	// bit 31 Lock
} CR_Bits;

typedef struct
{
	volatile uint32_t OPTLOCK :1;   // bit 0 Option lock
	volatile uint32_t OPTSTRT :1;   // bit 1 Option start
	volatile uint32_t BOR_LEV :2;   // bits 2–3 BOR reset level
	volatile uint32_t RESERVED1 :1;
	volatile uint32_t USER :3;
	volatile uint32_t RDP :8;
	volatile uint32_t nWRP :12;
	volatile uint32_t RESERVED2 :4;
} OPTCR_Bits;

typedef struct {
	ACR_Bits			ACR;       // 0x00 Access control
	KEYR_Bits 			KEYR;      // 0x04 Key register
	OPTKEYR_Bits 		OPTKEYR; // 0x08 Option key register
	SR_Bits 			SR;        // 0x0C Status register
	CR_Bits 			CR;        // 0x10 Control register
	volatile uint32_t 	AR;       // 0x14 Address register
	OPTCR_Bits 			OPTCR;     // 0x18 Option control register
} FLASH_t;

#define FLASH (*(FLASH_t*)0x40023C00UL)

// Sector base addresses (F407)
static const uint32_t FLASH_SECTOR_BASE[12] = {
		0x08000000UL, // S0  16KB
		0x08004000UL, // S1  16KB
		0x08008000UL, // S2  16KB
		0x0800C000UL, // S3  16KB
		0x08010000UL, // S4  64KB
		0x08020000UL, // S5 128KB
		0x08040000UL, // S6 128KB
		0x08060000UL, // S7 128KB
		0x08080000UL, // S8 128KB
		0x080A0000UL, // S9 128KB
		0x080C0000UL, // S10 128KB
		0x080E0000UL  // S11 128KB
};

static const uint32_t FLASH_SECTOR_SIZE[12] = {
		16 * 1024U,
		16 * 1024U,
		16 * 1024U,
		16 * 1024U,
		64 * 1024U,
		128 * 1024U,
		128 * 1024U,
		128 * 1024U,
		128 * 1024U,
		128 * 1024U,
		128 * 1024U,
		128 * 1024U
};

/* Flash unlock keys */
#define FLASH_KEY1 		0x45670123UL
#define FLASH_KEY2 		0xCDEF89ABUL
#define FLASH_OPTKEY1 	0x08192A3BUL
#define FLASH_OPTKEY2 	0x4C5D6E7FUL

void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_EraseSector(uint8_t);
void FLASH_WriteWord(uint32_t, uint32_t);
uint32_t FLASH_ReadWord(uint32_t);
void FLASH_ClearFlags(void);

#endif /* FLASH_H_ */
