/*
 * sysTick.h
 *
 *  Created on: 27-Nov-2025
 *      Author: skani
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#define SystemCoreClock	16000000

typedef struct {
    // Control & Status Register (CTRL)
    struct {
        volatile uint32_t ENABLE     :1;  // Counter enable
        volatile uint32_t TICKINT    :1;  // Interrupt enable
        volatile uint32_t CLKSOURCE  :1;  // Clock source (0=external, 1=CPU)
        volatile uint32_t RESERVED   :13; // Reserved
        volatile uint32_t COUNTFLAG  :1;  // Set when timer counts to 0
        volatile uint32_t RESERVED2  :15; // Reserved
    } CTRL;

    // Reload Value Register (LOAD)
    struct {
        volatile uint32_t RELOAD     :24; // Reload value
        volatile uint32_t RESERVED   :8;  // Reserved
    } LOAD;

    // Current Value Register (VAL)
    struct {
        volatile uint32_t CURRENT    :24; // Current value
        volatile uint32_t RESERVED   :8;  // Reserved
    } VAL;

    // Calibration Register (CALIB)
    struct {
        volatile uint32_t TENMS      :24; // 10ms calibration value
        volatile uint32_t RESERVED   :6;  // Reserved
        volatile uint32_t SKEW       :1;  // Calibration skew
        volatile uint32_t NOREF      :1;  // No reference clock
    } CALIB;

} SysTick_t;

// Map SysTick base address
#define SysTick ((SysTick_t *)0xE000E010)

void SysTick_Init(void);
void msDelay(uint32_t);

#endif /* SYSTICK_H_ */
