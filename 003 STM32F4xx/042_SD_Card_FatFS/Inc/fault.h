/*
 * fault.h
 *
 *  Created on: 07-Dec-2025
 *      Author: skani
 */

#ifndef FAULT_H_
#define FAULT_H_

#define SCB_CFSR   (*((volatile uint32_t*)0xE000ED28))
#define SCB_HFSR   (*((volatile uint32_t*)0xE000ED2C))
#define SCB_BFAR   (*((volatile uint32_t*)0xE000ED38))
#define SCB_MMFAR  (*((volatile uint32_t*)0xE000ED34))

#endif /* FAULT_H_ */
