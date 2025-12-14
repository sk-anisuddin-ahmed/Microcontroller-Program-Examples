/*
 * flash.c
 *
 *  Created on: 14-Dec-2025
 *      Author: skani
 */

#include "flash.h"

void FLASH_Unlock(void)
{
	FLASH_ClearFlags();
    __asm volatile ("cpsid i");   // Disable interrupts
    if (FLASH.CR.LOCK)
    {
        FLASH.KEYR.KEY = FLASH_KEY1;
        FLASH.KEYR.KEY = FLASH_KEY2;
    }
}

void FLASH_Lock(void)
{
    FLASH.CR.LOCK = 1;
    __asm volatile ("cpsie i");   // Re-enable interrupts
    FLASH_ClearFlags();
}

void FLASH_ClearFlags(void)
{
    FLASH.SR.EOP    = 1;
    FLASH.SR.OPERR  = 1;
    FLASH.SR.WRPERR = 1;
    FLASH.SR.PGAERR = 1;
    FLASH.SR.PGPERR = 1;
    FLASH.SR.PGSERR = 1;
}

void FLASH_EraseSector(uint8_t sector)
{
    // Wait if busy
    while (FLASH.SR.BSY);

    FLASH_Unlock();

    FLASH.CR.SER  = 1;       // Sector erase
    FLASH.CR.SNB  = sector;  // Select sector
    FLASH.CR.PSIZE = 0x2;    // 32-bit parallelism
    FLASH.CR.STRT = 1;       // Start erase

    while (FLASH.SR.BSY);    // Wait until done

    FLASH.CR.SER = 0;        // Clear erase bit
    FLASH.CR.SNB = 0;        // Clear sector number
    FLASH.CR.PSIZE = 0;

    FLASH_Lock();
}

void FLASH_WriteWord(uint32_t address, uint32_t data)
{
    while (FLASH.SR.BSY);

    FLASH_Unlock();

    FLASH.CR.PG    = 1;      // Enable programming
    FLASH.CR.PSIZE = 0x2;    // Program size = 32-bit word

    *(volatile uint32_t*)address = data;

    while (FLASH.SR.BSY);    // Wait until done

    FLASH.CR.PG = 0;         // Disable programming
    FLASH.CR.PSIZE = 0;

    FLASH_Lock();
}

uint32_t FLASH_ReadWord(uint32_t address)
{
    return *(volatile uint32_t*)address;
}
