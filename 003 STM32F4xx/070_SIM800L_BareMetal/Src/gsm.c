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
    	buffer[i] = UART2_ReadChar(2000);
		if (buffer[i] == GSM_TIMEOUT_CHAR)
		{
			break;
        }
    }
	buffer[i] = '\0';
}

_Bool GSM_Send_Check(const char *cmd, const char *resp, int tryLimit)
{
	char respRec[64];
	for (int try = 0; try < tryLimit; try++)
	{
		GSM_Send(cmd);
		GSM_ReadLine(respRec, sizeof(respRec));
		printf("Command: %s, Response: %s", cmd, respRec);
		if (strstr(respRec, resp))
		{
			printf(" > Success\n");
			return 1;
		}
		else
		{
			printf(" > Failure\n");
		}
	}
	return 0;
}

_Bool GSM_Init(void)
{
	// Test communication
	if (!GSM_Send_Check("AT", "OK", 5))
	{
	    return 0;
	}

	// Disable echo (cleaner responses)
	if (!GSM_Send_Check("ATE0", "OK", 5))
	{
	    return 0;
	}

	// Fix baud rate (optional, if not using auto-baud)
	if (!GSM_Send_Check("AT+IPR=9600", "OK", 5))
	{
	    return 0;
	}

	// Check SIM status
	if (!GSM_Send_Check("AT+CPIN?", "READY",5))
	{
	    return 0;
	}

	// Check network registration
	if (!GSM_Send_Check("AT+CREG?", "OK", 5))
	{
	    return 0;
	// Expect +CREG: 0,1 or 0,5 in response
	}

	// Enable caller ID
	if (!GSM_Send_Check("AT+CLIP=1", "OK", 5))
	{
	    return 0;
	}

	// Set SMS text mode
	if (!GSM_Send_Check("AT+CMGF=1", "OK", 5))
	{
	    return 0;
	}

	// Configure new SMS indications
	if (!GSM_Send_Check("AT+CNMI=1,2,0,0,0", "OK", 5))
	{
	    return 0;
	}

	// Query signal quality
	if (!GSM_Send_Check("AT+CSQ", "OK", 5))
	{
	    return 0;
	// Response will be +CSQ: <rssi>,<ber>
	}

	// Query current operator
	if (!GSM_Send_Check("AT+COPS?", "OK", 5))
	{
	    return 0;
	}

	// Send BootUp SMS
	return  GSM_SendSMS("+919231244540", "Hello from STM32!");
}

void GSM_Log(const char *resp)
{
	static char number[32];
	static char name[64];
	static char smsBody[256];
	memset(number, 	'\0', sizeof(number));
	memset(name, 	'\0', sizeof(name));
	memset(smsBody, '\0', sizeof(smsBody));

    if (strstr(resp, "+CLIP:"))
    {
        Parse_Call_Details(resp, number, name);
        printf("Incoming Call from %s %s\n", name, number);
    }
    else if (strstr(resp, "RING"))
	{
		printf("Unknown Call Incoming\n");
	}
    else if (strstr(resp, "+CM"))
    {

		Parse_SMS_Details(resp, number, name, smsBody);
		printf("SMS from %s %s: %s\n", name, number, smsBody);
    }
}

_Bool GSM_SendSMS(const char *number, const char *text)
{
    char resp[128];

    printf("Sending SMS to %s\n", number);

    sprintf(resp, "AT+CMGS=\"%s\"", number);
    if (!GSM_Send_Check(resp,">", 3))
    {
    	printf("SMS Command Failure\n");
        return 0;
    }

    GSM_Send(text);
    UART2_WriteChar(26);

    GSM_ReadLine(&resp[0], 128);
    if (strstr(resp, "+CMGS") || strstr(resp, "OK"))
    {
        return 1;
    }
    return 0;
}

void Parse_Call_Details(const char *resp, char *number, char *name) {
    int quoteCount = 0;
    const char* p = resp;

    while (*p) {
        if (*p == '"') {
            quoteCount++;
            if (quoteCount == 1) {
                const char *start = p + 1;
                const char *end = strchr(start, '"');
                if (end) {
                    strncpy(number, start, end - start);
                    number[end - start] = '\0';
                }
            }
            else if (quoteCount == 5) {
                const char *start = p + 1;
                const char *end = strchr(start, '"');
                if (end) {
                    strncpy(name, start, end - start);
                    name[end - start] = '\0';
                }
                break;
            }
        }
        p++;
    }
}

void Parse_SMS_Details(const char *resp, char *number, char *name, char *text) {
    int quoteCount = 0;
    const char* p = resp;

    while (*p) {
        if (*p == '"') {
            quoteCount++;
            if (quoteCount == 1) {
                const char *start = p + 1;
                const char *end = strchr(start, '"');
                if (end) {
                    strncpy(number, start, end - start);
                    number[end - start] = '\0';
                }
            }
            else if (quoteCount == 3) {
                const char *start = p + 1;
                const char *end = strchr(start, '"');
                if (end) {
                    strncpy(name, start, end - start);
                    name[end - start] = '\0';
                }
            }
            else if (quoteCount == 6) {
				const char *start = p + 1;
				const char *end = strchr(start, '\0');
				if (end) {
					strncpy(text, start, end - start);
					text[end - start] = '\0';
				}
				break;
			}
        }
        p++;
    }
}
