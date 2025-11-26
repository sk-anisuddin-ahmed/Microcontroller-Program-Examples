/*
 * FreeRTOSConfig.h
 *
 *  Created on: 26-Nov-2025
 *      Author: skani
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "stm32f4xx_hal.h"   // Needed for SystemCoreClock and NVIC priority bits

/*-----------------------------------------------------------
 * Application specific definitions.
 * Adjust these values for your project.
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION                    1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_TICKLESS_IDLE                 0
#define configCPU_CLOCK_HZ                      (84000000)
#define configTICK_RATE_HZ                      ((TickType_t)1000)
#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                ((unsigned short)128)
#define configTOTAL_HEAP_SIZE                   ((size_t)(20*1024))
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1

#define configUSE_MUTEXES                       1
#define configUSE_COUNTING_SEMAPHORES           1
#define configCHECK_FOR_STACK_OVERFLOW          2

#define INCLUDE_vTaskDelay 						1
#define INCLUDE_vTaskDelete 					1

/* Hook functions */
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0

/* Run-time stats (optional) */
#define configGENERATE_RUN_TIME_STATS           0

/*-----------------------------------------------------------
 * Cortex-M specific definitions
 *----------------------------------------------------------*/

/* Number of priority bits implemented in the NVIC (STM32F4 = 4) */
#define configPRIO_BITS                         __NVIC_PRIO_BITS

/* Lowest interrupt priority */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 0xf

/* Highest interrupt priority from which FreeRTOS API calls can be made */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

/* Kernel interrupt priority */
#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Maximum syscall interrupt priority */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#endif /* FREERTOS_CONFIG_H */
