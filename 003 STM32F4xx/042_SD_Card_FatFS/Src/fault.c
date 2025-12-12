/*
 * isr.c
 *
 *  Created on: 07-Dec-2025
 *      Author: skani
 */

#include <stdint.h>
#include "fault.h"

// System exception handlers
void NMI_Handler(void)
{
	while (1);
}

void HardFault_Handler(void)
{
	while (1);
}
void MemManage_Handler(void)
{
	while (1);
}
void BusFault_Handler(void)
{
	while (1);
}
void UsageFault_Handler(void)
{
	while (1);
}
void SVC_Handler(void)
{
	while (1);
}
void DebugMon_Handler(void)
{
	while (1);
}
void PendSV_Handler(void)
{
	while (1);
}