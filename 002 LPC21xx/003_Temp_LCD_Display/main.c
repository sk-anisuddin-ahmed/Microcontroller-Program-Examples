#include <LPC21xx.h>
#include <stdio.h>
#include <string.h>
#include "clock.h"
#include "timer.h"
#include "gpio.h"
#include "lcd.h"
#include "adc.h"

extern int temp_adc;
double temp_float_adc;
char temp_adc_buf[32];

int main(void)
{   
    __disable_irq();
    CLOCK_INIT();
    GPIO_INIT();
    ADC_POLLING_INIT();
    TIMER_INIT();
    LCD_BEGIN();
    __enable_irq();
    
    LCD_CLEAR();
    LCD_SET_CURSOR(0, 1);
    LCD_SEND_STRING("STARTING.....");    
    memset(temp_adc_buf, '\0', sizeof(temp_adc_buf));
    
    while(1)
    {
        T1_delay_ms(1000);
        ADC_Value_Fetch();

        // Convert ADC value to temperature
        double v_adc     = (temp_adc / (double)1023.0) * 3.3;       // voltage at ADC pin
        double v_sensor  = v_adc * (5.0 / 3.3);             				// scaled back to sensor voltage
        temp_float_adc   = v_sensor * 100.0;                				// 0.01 V = 1 °C

        LCD_CLEAR();
        LCD_SET_CURSOR(0, 0);
        LCD_SEND_STRING("LPC2138 TEMP LOG");

        sprintf(temp_adc_buf, "Temp C = %.2f", temp_float_adc);         
        LCD_SET_CURSOR(0, 1);
        LCD_SEND_STRING(temp_adc_buf);          

        memset(temp_adc_buf, '\0', sizeof(temp_adc_buf));
    }
}
