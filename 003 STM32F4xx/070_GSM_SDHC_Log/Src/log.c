#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ff.h"
#include "diskio.h"

FATFS fs;
FIL file;

bool Logger_Init(void)
{
    FRESULT resp = f_mount(&fs, "0:/", 1);
    if (resp != FR_OK)
    {
        printf("Drive 0:/ Mount Failed\n");
        return 0;
    }
    printf("Drive 0:/ Mounted\n");
    return 1;
}

void Logger_OpenFile(const char *filename)
{
    UINT bw;
    FRESULT resp = f_open(&file, filename, FA_WRITE | FA_OPEN_APPEND);
    if (resp == FR_OK)
    {
        printf("Opened: %s\n", filename);
        if (f_size(&file) == 0)
        {
            const char *str = "Timestamp,	SensorData\n";
            if (f_write(&file, str, strlen(str), &bw) == FR_OK)
            {
                printf("Wrote to %s\n", filename);
            }
            else
            {
                printf("Failed to write file\n");
            }
        }
        if (f_close(&file) == FR_OK)
        {
            printf("%s Closed Successfully\n", filename);
        }
        else
        {
            printf("Failed to close %s\n", filename);
        }
    }
    else
    {
        printf("Failed to open file: %s", filename);
    }
}

void Logger_LogEntry(const char *filename, int s1)
{
    FRESULT resp;
    char buffer[128];
    char timestamp[32] = "2025-12-07 18:45:00";
    UINT bw;

    sprintf(buffer, "%s,	%d\n", timestamp, s1);

    if (f_open(&file, filename, FA_WRITE | FA_OPEN_APPEND) == FR_OK)
    {
        printf("Opened: %s", filename);
        resp = f_write(&file, buffer, strlen(buffer), &bw);
        resp &= f_close(&file);
        if (resp == FR_OK)
        {
            printf("Logger entry done\n");
        }
        else
        {
            printf("Logger entry failed\n");
        }
    }
    else
    {
        printf("Logger entry failed\n");
    }
}

void Logger_ReadFile(const char *filename)
{
    char buffer[128];
    UINT br;

    if (f_open(&file, filename, FA_READ) == FR_OK)
    {
        printf("Opened: %s", filename);
        while (f_read(&file, buffer, sizeof(buffer) - 1, &br) == FR_OK && br > 0)
        {
            buffer[br] = '\0';
        }
        printf("Read %d Bytes - \n", (int)br);
        printf("%s\n", buffer);
        if (f_close(&file) == FR_OK)
        {
            printf("%s Closed Successfully\n", filename);
        }
        else
        {
            printf("Failed to close %s\n", filename);
        }
    }
    else
    {
        printf("Failed to open file: %s", filename);
    }
}

void Logger_DeleteFile(const char *filename)
{
    if (f_unlink(filename) == FR_OK)
    {
        printf("Deleted %s\n", filename);
    }
    else
    {
        printf("Failed to delete %s\n", filename);
    }
}
