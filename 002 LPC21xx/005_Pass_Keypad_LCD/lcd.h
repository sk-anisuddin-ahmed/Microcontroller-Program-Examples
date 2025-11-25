#include <stdint.h>

#define DATA 1
#define COMMAND 0

#define HIGH 1
#define LOW 0

//Initializing Pins
#define D4_HIGH (IO1SET |= ((unsigned long)1 << 20))
#define D4_LOW  (IO1CLR |= ((unsigned long)1 << 20))

#define D5_HIGH (IO1SET |= ((unsigned long)1 << 21))
#define D5_LOW  (IO1CLR |= ((unsigned long)1 << 21))

#define D6_HIGH (IO1SET |= ((unsigned long)1 << 22))
#define D6_LOW  (IO1CLR |= ((unsigned long)1 << 22))

#define D7_HIGH (IO1SET |= ((unsigned long)1 << 23))
#define D7_LOW  (IO1CLR |= ((unsigned long)1 << 23))

#define RS_HIGH (IO0SET |= ((unsigned long)1 << 29))	//Register Select
#define RS_LOW  (IO0CLR |= ((unsigned long)1 << 29))	

#define EN_HIGH (IO0SET |= ((unsigned long)1 << 31))	//Enable
#define EN_LOW  (IO0CLR |= ((unsigned long)1 << 31))

void LCD_PIN_INIT(void);
void LCD_BEGIN(void);
void LCD_CLEAR(void);
void LCD_WRITE_NIBBLE(uint8_t);
void LCD_WRITE_CHAR(uint8_t);
void LCD_COMMAND(uint8_t);
void LCD_COMMAND_4BIT(uint8_t);
void LCD_WRITE_8BIT(uint8_t);
void LCD_SET_CURSOR(uint8_t, uint8_t);
void LCD_SEND_STRING(char[32]);
void LCD_ENABLE_PULSE(void);
