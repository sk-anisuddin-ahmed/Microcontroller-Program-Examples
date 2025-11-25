#ifndef I2C_H
#define I2C_H

#include "stm32f4xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

void I2C1_Init(void);

extern uint8_t rxData[];
extern uint8_t reg;

#endif
