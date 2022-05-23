/**
 * RP2040 FreeRTOS Template
 *
 * @copyright 2022, Tony Smith (@smittytone)
 * @version   1.3.0
 * @license   MIT
 *
 */
#ifndef _MAIN_H_
#define _MAIN_H_


// FreeRTOS
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
// C
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
// Pico SDK
#include "pico/stdlib.h"            // Includes `hardware_gpio.h`
#include "pico/binary_info.h"


#ifdef __cplusplus
extern "C" {
#endif


/**
 * CONSTANTS
 */
#define         RED_LED_PIN           20


/**
 * PROTOTYPES
 */
void led_task_pico(void* unused_arg);
void led_task_gpio(void* unused_arg);
void log_debug(const char* msg);
void log_device_info(void);


#ifdef __cplusplus
}           // extern "C"
#endif


#endif      // _MAIN_H_
