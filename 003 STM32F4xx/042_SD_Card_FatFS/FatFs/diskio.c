#include "ff.h"
#include "diskio.h"
#include "spi.h"
#include "sdcmd.h"

#define SD_CARD 0

DSTATUS disk_status(BYTE pdrv)
{
    if (pdrv == SD_CARD)
    {
        return SD_CheckReady() ? 0 : STA_NOINIT;
    }
    return STA_NOINIT;
}

DSTATUS disk_initialize(BYTE pdrv)
{
    if (pdrv == SD_CARD)
    {
        return (SD_Init() == 0) ? 0 : STA_NOINIT;
    }
    return STA_NOINIT;
}

DRESULT disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
    if (pdrv != SD_CARD)
        return RES_PARERR;

    for (UINT i = 0; i < count; i++)
    {
        if (SD_ReadBlock(buff + (i * 512), sector + i) != 0)
        {
            return RES_ERROR;
        }
    }
    return RES_OK;
}

DRESULT disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
    if (pdrv != SD_CARD)
        return RES_PARERR;

    for (UINT i = 0; i < count; i++)
    {
        if (SD_WriteBlock(buff + (i * 512), sector + i) != 0)
        {
            return RES_ERROR;
        }
    }
    return RES_OK;
}

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
    if (pdrv != SD_CARD)
        return RES_PARERR;

    switch (cmd)
    {
    case CTRL_SYNC:
        SD_WaitReady();
        return RES_OK;

    case GET_SECTOR_COUNT:
        *(DWORD *)buff = SD_GetSectorCount();
        return RES_OK;

    case GET_SECTOR_SIZE:
        *(WORD *)buff = 512;
        return RES_OK;

    case GET_BLOCK_SIZE:
        *(DWORD *)buff = 1;
        return RES_OK;

    default:
        return RES_PARERR;
    }
}
