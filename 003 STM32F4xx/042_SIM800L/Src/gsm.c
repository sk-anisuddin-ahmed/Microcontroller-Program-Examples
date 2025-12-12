/*
 * gsm.c
 *
 *  Created on: 12-Dec-2025
 *      Author: skani
 */

#include "gsm.h"
#include "sysTick.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>

void GSM_Send(const char *cmd)
{
	UART2_WriteString(cmd);
	UART2_WriteString("\r\n");
}

void GSM_ReadLine(char *buffer, int maxLen)
{
	int i;
	for (i = 0; i < maxLen - 1; i++)
    {
    	buffer[i] = UART2_ReadChar();
		if (buffer[i] == '\n')
		{
			break;
        }
    }
    buffer[i] = '\0';
}

_Bool GSM_Send_Check(const char *cmd, const char *resp, int respLen, int tryLimit)
{
	char respRec[64];
	for (int try = 0; try < respLen; try++)
	{
		GSM_Send(cmd);
		GSM_ReadLine(respRec, sizeof(respRec));
		if (strstr(respRec, resp))
		{
			return 1;
		}
	}
	return 0;
}

_Bool GSM_Init(void)
{
	// Test communication
	if (!GSM_Send_Check("AT", "OK", 64, 3))
	{
		return 0;
	}
	// Set SMS text mode
	if (!GSM_Send_Check("AT+CMGF=1", "OK", 64, 3))
	{
		return 0;
	}
	// Enable caller ID
	if (!GSM_Send_Check("AT+CLIP=1", "OK", 64, 3))
	{
		return 0;
	}
	// Configure new SMS indications
	if (!GSM_Send_Check("AT+CNMI=1,2,0,0,0", "OK", 64, 3))
	{
		return 0;
	}
	// Optional: check network registration
	if (!GSM_Send_Check("AT+CREG?", "+CREG: 0,1", 64, 5) &&
		!GSM_Send_Check("AT+CREG?", "+CREG: 0,5", 64, 5))
	{
		return 0;
	}

	// Send BootUp SMS
	return  GSM_SendSMS("+919231244540", "Hello from STM32!\r\n");
}

void GSM_Log(const char *resp)
{
    if (strstr(resp, "RING"))
    {
        printf("Unknown Call Incoming\n");
    }
    else if (strstr(resp, "+CLIP:"))
    {
        char number[32];
        sscanf(resp, "+CLIP: \"%31[^\"]", number);
        printf("Incoming Call from %s\n", number);
    }
    else if (strstr(resp, "+CMT:"))
    {
        char number[32];
        char smsBody[160];
        sscanf(resp, "+CMT: \"%31[^\"]", number);
        GSM_ReadLine(smsBody, sizeof(smsBody));
        printf("SMS Receive from %s\n", number);
        printf("%s\n", smsBody);
    }
}

_Bool GSM_SendSMS(const char *number, const char *text)
{
    char resp[128];

    sprintf(resp, "AT+CMGS=\"%s\"", number);
    GSM_Send(resp);

    GSM_ReadLine(resp, sizeof(resp));
    if (strstr(resp, ">") == NULL)
    {
        return 0;
    }

    UART2_WriteString(text);
    UART2_WriteString("\r\n");

    UART2_WriteChar(26);

    GSM_ReadLine(resp, sizeof(resp));
    if (strstr(resp, "+CMGS") || strstr(resp, "OK"))
    {
        return 1;
    }
    return 0;
}
