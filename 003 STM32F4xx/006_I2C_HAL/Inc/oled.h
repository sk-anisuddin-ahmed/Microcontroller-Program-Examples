/*
 * oled.h
 *
 *  Created on: 25-Nov-2025
 *      Author: skani
 */

#ifndef OLED_H_
#define OLED_H_

void OLED_Init(void);
void OLED_SendCommand(uint8_t);
void OLED_SendData(uint8_t);

#endif /* OLED_H_ */
