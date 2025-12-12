/*
 * gsm.h
 *
 *  Created on: 12-Dec-2025
 *      Author: skani
 */

#ifndef GSM_H_
#define GSM_H_

void GSM_Send(const char *);
void GSM_ReadLine(char *, int );
_Bool GSM_Send_Check(const char *, const char *, int , int );
_Bool GSM_Init(void);
void GSM_Log(const char *);
_Bool GSM_SendSMS(const char *, const char *);

#endif /* GSM_H_ */
