#define DATA 1
#define COMMAND 0

#define HIGH 1
#define LOW 0

#include "gpio.h"

//Initializing Pins
#define D4 GPIOD.ODR.PIN9 //4Bit Mode Data Pins
#define D5 GPIOD.ODR.PIN10
#define D6 GPIOD.ODR.PIN11
#define D7 GPIOD.ODR.PIN8
#define RS GPIOD.ODR.PIN0 //Register Select
#define EN GPIOD.ODR.PIN1 //Enable

void LCD_PIN_INIT(void);
void LCD_BEGIN();
void LCD_CLEAR(void);
void LCD_WRITE_NIBBLE(uint8_t);
void LCD_WRITE_CHAR(uint8_t);
void LCD_COMMAND(uint8_t);
void LCD_COMMAND_4BIT(uint8_t);
void LCD_WRITE_8BIT(uint8_t);
void LCD_SET_CURSOR(uint8_t, uint8_t);
void LCD_SEND_STRING(char*);
void LCD_ENABLE_PULSE();



