/*
 * logger.h
 *
 *  Created on: 07-Dec-2025
 *      Author: skani
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int Logger_Init(void);
void Logger_OpenFile(const char*);
void Logger_LogEntry(const char*, int);
void Logger_ReadFile(const char*);
void Logger_DeleteFile(const char*);

#endif /* LOG_H_ */
