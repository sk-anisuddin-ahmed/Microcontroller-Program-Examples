#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "ff.h"
#include "diskio.h"
#include "spi.h"
#include "sdcmd.h"
#include "sysTick.h"

int SD_CardType = CARD_UNKNOWN;

static uint8_t SD_SendCommand(uint8_t cmd, uint32_t arg)
{
	printf("***** SD CMD: %d *****\n", (int)cmd);
	uint8_t data[8];
	uint8_t crc = 0xFF;

	if (!SD_WaitReady())
	{
		return 0xFF;
	}

	SPI_CS_Control(CS_LOW);

	if (cmd == SD_CMD_GO_IDLE_STATE)
		crc = 0x95;
	else if (cmd == SD_CMD_SEND_IF_COND)
		crc = 0x87;

	data[0] = ((0x40 | cmd) & 0xFF);
	data[1] = ((arg >> 24) & 0xFF);
	data[2] = ((arg >> 16) & 0xFF);
	data[3] = ((arg >> 8) & 0xFF);
	data[4] = (arg & 0xFF);
	data[5] = (crc & 0xFF);

	printf("SPI TX: ");
	for (int i = 0; i < 6; i++)
	{
		printf("0x%X ", data[i]);
		SPI_Transfer(data[i]);
	}
	printf("\n");

	uint8_t resp = 0xFF;
	for (int try = 0; try < 8; try++)
	{
		resp = SPI_Transfer(0xFF);
		if ((resp & 0x80) == 0)
			break;
	}

	printf("SPI RX: 0x%X\n", resp);
	return resp;
}

bool SD_WaitReady(void)
{
	uint8_t resp;
	SPI_CS_Control(CS_LOW);

	for (int try = 0; try < 8; try++)
	{
		resp = SPI_Transfer(0xFF);
		if (resp == 0xFF)
		{
			printf("SD Card Ready\n");
			return 1;
		}
	}

	printf("SD Card Wait-Ready Timeout\n");
	SPI_CS_Control(CS_HIGH);
	SPI_Transfer(0xFF);
	return 0;
}

int SD_CheckReady(void)
{
	SPI_CS_Control(CS_LOW);
	int ready = (SPI_Transfer(0xFF) == 0xFF);
	SPI_CS_Control(CS_HIGH);
	SPI_Transfer(0xFF);
	if (ready)
		printf("SD Card Ready\n");
	else
		printf("SD Card Not Ready\n");
	return ready;
}

int SD_Init(void)
{
	printf("Initializing SD Card...\n");
	uint8_t resp;
	uint8_t r7[4], ocr[4];

	// 80 dummy clocks with CS high
	printf("Sending Dummy Clock\nResponse: ");
	SPI_CS_Control(CS_HIGH);
	for (int i = 0; i < 10; i++)
	{
		printf("0x%X ", SPI_Transfer(0xFF));
	}
	printf("\n");

	// CMD0: GO_IDLE_STATE
	resp = SD_SendCommand(SD_CMD_GO_IDLE_STATE, 0);
	if (resp != 0x01)
	{
		printf("CMD0 Failed\n");
		return -1;
	}

	// CMD59: CRC_OFF
	resp = SD_SendCommand(SD_CMD_CRC_ON_OFF, 0);
	if (resp != 0x01)
	{
		printf("CMD59 Failed\n");
		return -2;
	}

	// CMD8: SEND_IF_COND
	resp = SD_SendCommand(SD_CMD_SEND_IF_COND, 0x1AA);
	if (resp == 0x01)
	{
		for (int i = 0; i < 4; i++)
			r7[i] = SPI_Transfer(0xFF);
		if (r7[2] != 0x01 || r7[3] != 0xAA)
		{
			printf("CMD8 Check Failed\n");
			return -3;
		}

		// ACMD41 loop until ready
		for (int try = 0; try < 8; try++)
		{
			resp = SD_SendCommand(SD_CMD_APP_CMD, 0);
			if ((resp == 0x00) || (resp == 0x01))
			{
				resp = SD_SendCommand(SD_ACMD_SEND_OP_COND, 0x40000000);
				if (resp == 0x00)
				{
					break;
				}
			}
		}
		if (resp != 0x00)
		{
			printf("ACMD41 Failed\n");
			return -4;
		}

		// CMD58: READ_OCR
		resp = SD_SendCommand(SD_CMD_READ_OCR, 0);
		if (resp != 0x00)
		{
			printf("CMD58 Failed\n");
			return -5;
		}
		for (int i = 0; i < 4; i++)
			ocr[i] = SPI_Transfer(0xFF);
		SD_CardType = (ocr[0] & 0x40) ? CARD_SDHC : CARD_SD;
		printf("Card Type: %s\n", (SD_CardType == CARD_SDHC) ? "SDHC [New]" : "SDSC [Old]");
	}

	// CMD16: SET_BLOCKLEN (only for SDSC/MMC)
	if (SD_CardType != CARD_SDHC)
	{
		resp = SD_SendCommand(SD_CMD_SET_BLOCKLEN, 512);
		if (resp != 0x00)
		{
			printf("CMD16 Failed\n");
			return -7;
		}
	}

	SD_GetSectorCount();
	printf("SD Init Success\n");
	return 0;
}

int SD_ReadBlock(uint8_t *buff, uint32_t sector)
{
	printf("Reading Sector = %lu\n", sector);
	uint32_t addr = (SD_CardType == CARD_SDHC) ? sector : (sector * 512);

	uint8_t resp = SD_SendCommand(SD_CMD_READ_SINGLE_BLOCK, addr);
	for (int try = 0; try < 8; try++)
	{
		if (resp == 0x00)
			break;
		else
			resp = SD_SendCommand(SD_CMD_READ_SINGLE_BLOCK, addr);
	}
	if (resp != 0x00)
	{
		SPI_CS_Control(CS_HIGH);
		SPI_Transfer(0xFF);
		printf("CMD17 failed\n");
		return -1;
	}

	uint32_t start = msTicks;
	do
	{
		resp = SPI_Transfer(0xFF);
	} while ((resp == 0xFF) && ((msTicks - start) < 1000));

	if (resp != 0xFE)
	{
		SPI_CS_Control(CS_HIGH);
		SPI_Transfer(0xFF);
		printf("CMD17 Read Response Failed\n");
		return -2;
	}

	for (int i = 0; i < 512; i++)
		buff[i] = SPI_Transfer(0xFF);

	SPI_Transfer(0xFF);
	SPI_Transfer(0xFF);
	SPI_CS_Control(CS_HIGH);
	SPI_Transfer(0xFF);

	printf("***** Sector %lu Data *****\n", (unsigned long)sector);
	for (int i = 0; i < 512; i += 8)
	{
	    printf("%03d: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
	           i,
	           buff[i], buff[i+1], buff[i+2], buff[i+3],
	           buff[i+4], buff[i+5], buff[i+6], buff[i+7]);
	}

	printf("Read-Block Success\n");
	return 0;
}

int SD_WriteBlock(const uint8_t *buff, uint32_t sector)
{
	printf("Writing Sector = %lu\n", sector);
	uint32_t addr = (SD_CardType == CARD_SDHC) ? sector : sector * 512;

	uint8_t resp = SD_SendCommand(SD_CMD_WRITE_SINGLE_BLOCK, addr);
	for (int try = 0; try < 8; try++)
	{
		if (resp == 0x00)
			break;
		else
			resp = SD_SendCommand(SD_CMD_WRITE_SINGLE_BLOCK, addr);
	}
	if (resp != 0x00)
	{
		SPI_CS_Control(CS_HIGH);
		SPI_Transfer(0xFF);
		printf("CMD24 Failed\n");
		return -1;
	}

	SPI_Transfer(0xFE);
	for (int i = 0; i < 512; i++)
		SPI_Transfer(buff[i]);
	SPI_Transfer(0xFF);
	SPI_Transfer(0xFF);

	resp = SPI_Transfer(0xFF);
	if ((resp & 0x1F) != 0x05)
	{
		SPI_CS_Control(CS_HIGH);
		SPI_Transfer(0xFF);
		printf("Write Data Rejected\n");
		return -2;
	}
	else
	{
		printf("Write Data Accepted\n");
	}

	uint32_t start = msTicks;
	do
	{
		resp = SPI_Transfer(0xFF);
	} while ((resp != 0xFF) && ((msTicks - start) < 1000));
	if (resp != 0xFF)
	{
		printf("Card Release Timeout\n");
	}
	else
	{
		printf("Write-Block Success\n");
	}

	SPI_CS_Control(CS_HIGH);
	SPI_Transfer(0xFF);
	return 0;
}

int SD_ReadCSD(uint8_t *csd)
{
	printf("Reading CSD...\n");
	if (SD_SendCommand(SD_CMD_SEND_CSD, 0) != 0x00)
	{
		SPI_CS_Control(CS_HIGH);
		SPI_Transfer(0xFF);
		printf("CMD9 Failed\n");
		return -1;
	}

	uint8_t resp;
	uint32_t start = msTicks;
	do
	{
		resp = SPI_Transfer(0xFF);
	} while ((resp == 0xFF) && ((msTicks - start) < 1000));

	if (resp != 0xFE)
	{
		SPI_CS_Control(CS_HIGH);
		SPI_Transfer(0xFF);
		printf("CSD Token Failed\n");
		return -2;
	}

	for (int i = 0; i < 16; i++)
		csd[i] = SPI_Transfer(0xFF);

	SPI_Transfer(0xFF);
	SPI_Transfer(0xFF);
	SPI_CS_Control(CS_HIGH);
	SPI_Transfer(0xFF);
	printf("ReadCSD Success\n");
	return 0;
}

DWORD SD_GetSectorCount(void)
{
	uint8_t csd[16];
	if (SD_ReadCSD(csd) != 0)
	{
		SPI_CS_Control(CS_HIGH);
		SPI_Transfer(0xFF);
		return 0;
	}

	DWORD sectors = 0;

	if ((csd[0] >> 6) == 1)
	{
		// SDHC/SDXC (CSD v2.0)
		DWORD c_size = ((DWORD)(csd[7] & 0x3F) << 16) |
					   ((DWORD)csd[8] << 8) |
					   csd[9];
		sectors = (c_size + 1) * 1024; // number of 512-byte blocks
	}
	else
	{
		// SDSC (CSD v1.0)
		DWORD c_size = ((csd[6] & 0x03) << 10) | (csd[7] << 2) |
					   ((csd[8] & 0xC0) >> 6);
		DWORD mult = ((csd[9] & 0x03) << 1) | ((csd[10] & 0x80) >> 7);
		DWORD blocknr = (c_size + 1) * (1 << (mult + 2));
		sectors = blocknr; // number of 512-byte blocks
	}

	// Print card size in MB (integer only)
	DWORD mb = (sectors >> 11); // (sectors * 512) / (1024*1024) = sectors / 2048
	printf("Card size: %lu MB\n", (unsigned long)mb);

	return sectors;
}
