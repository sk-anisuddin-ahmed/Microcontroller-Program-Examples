#ifndef SDCMD_H
#define SDCMD_H

#include <stdbool.h>
#include <stdint.h>

// --- SD Card Responses ---
#define IDLE_STATE 0x01
#define READY 0x00
#define ILLEGAL_COMMAND 0x04
#define CRC_ERROR 0x08

// --- Block size ---
#define SD_BLOCK_SIZE 512

typedef enum
{
    CARD_NONE,
    CARD_MMC,
    CARD_SD,
    CARD_SDHC,
    CARD_UNKNOWN
} sdcard_type_t;

typedef enum
{
    // --- Basic commands ---
    SD_CMD_GO_IDLE_STATE = 0,      // CMD0: reset card, enter SPI mode
    SD_CMD_SEND_OP_COND = 1,       // CMD1: initialize (MMC, not SD)
    SD_CMD_SEND_CID = 2,           // CMD2: send CID (not used in SPI)
    SD_CMD_SEND_RELATIVE_ADDR = 3, // CMD3: send relative address (not used in SPI)
    SD_CMD_SEND_SWITCH_FUNC = 6,   // CMD6: switch function
    SD_CMD_SEND_IF_COND = 8,       // CMD8: check voltage range (2.7-3.6V)
    SD_CMD_SEND_CSD = 9,           // CMD9: read CSD register
    SD_CMD_SEND_CID_REGISTER = 10, // CMD10: read CID register
    SD_CMD_STOP_TRANSMISSION = 12, // CMD12: stop data transmission
    SD_CMD_SEND_STATUS = 13,       // CMD13: send card status

    // --- Block read/write ---
    SD_CMD_SET_BLOCKLEN = 16,         // CMD16: set block length (usually 512 bytes)
    SD_CMD_READ_SINGLE_BLOCK = 17,    // CMD17: read one 512-byte block
    SD_CMD_READ_MULTIPLE_BLOCK = 18,  // CMD18: read multiple blocks
    SD_CMD_SEND_NUM_WR_BLOCKS = 22,   // CMD22: number of written blocks
    SD_CMD_SET_WR_BLK_ERASE_CNT = 23, // CMD23: set write block erase count
    SD_CMD_WRITE_SINGLE_BLOCK = 24,   // CMD24: write one 512-byte block
    SD_CMD_WRITE_MULTIPLE_BLOCK = 25, // CMD25: write multiple blocks

    // --- Application-specific (ACMDxx, must be preceded by CMD55) ---
    SD_ACMD_SEND_OP_COND = 41,    // ACMD41: initialize card
    SD_ACMD_CLR_CARD_DETECT = 42, // ACMD42: clear card detect
    SD_ACMD_SEND_SCR = 51,        // ACMD51: read SCR register

    // --- Card control ---
    SD_CMD_APP_CMD = 55,   // CMD55: prefix for application-specific commands
    SD_CMD_READ_OCR = 58,  // CMD58: read operating conditions register
    SD_CMD_CRC_ON_OFF = 59 // CMD59: enable/disable CRC
} sdcard_command_t;

bool SD_WaitReady(void);
int SD_CheckReady(void);
int SD_Init(void);
int SD_ReadBlock(uint8_t *, uint32_t);
int SD_WriteBlock(const uint8_t *, uint32_t);
uint32_t SD_GetSectorCount(void);

#endif
