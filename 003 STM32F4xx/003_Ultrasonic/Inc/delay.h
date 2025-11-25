/*
 * delay.h
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#ifndef DELAY_H_
#define DELAY_H_

void DWT_Init(void);
void delayMicroseconds(uint32_t);
uint32_t elapsedMicroseconds(void);

#endif /* DELAY_H_ */
