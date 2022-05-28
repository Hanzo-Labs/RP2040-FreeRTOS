/**
 * RP2040 autosar initialization .. derived from Template example
 *
 * @author - Devendra Naga (devendra.aaru@outlook.com)
 * @copyright - 2022-present All rights reserved
 *
 */

#include "main.h"
#include <Det.h>


// Set a delay time of exactly 500ms
const TickType_t ms_delay = 500 / portTICK_PERIOD_MS;

TaskHandle_t pico_task_handle = NULL;
TaskHandle_t autosar_task_handle = NULL;

/**
 * @brief Repeatedly flash the Pico's built-in LED.
 */
void led_task_pico(void* unused_arg)
{
    // Store the Pico LED state
    uint8_t pico_led_state = 0;

    // Configure the Pico's on-board LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    while (true) {
        // Turn Pico LED on an add the LED state
        // to the FreeRTOS xQUEUE
        pico_led_state = !pico_led_state;
        gpio_put(PICO_DEFAULT_LED_PIN, pico_led_state);
        vTaskDelay(ms_delay);
    }
}

void autosar_task(void *data)
{
    int count = 0;
    Det_Init(NULL);

    while (true) {
        sleep_ms(1000);
        Det_ReportError(1, 1, 1, count);
        count = count + 1;
    }
}

/*
 * RUNTIME START
 */
int main()
{
    stdio_usb_init();

    // init LEDs for debugging
    BaseType_t pico_status = xTaskCreate(led_task_pico,
                                         "PICO_LED_TASK",
                                         128,
                                         NULL,
                                         1,
                                         &pico_task_handle);

    // setup autosar task
    BaseType_t autosar_status = xTaskCreate(autosar_task,
                                            "autosar_task",
                                            128,
                                            NULL,
                                            1,
                                            &autosar_task_handle);

    // Start the FreeRTOS scheduler
    // FROM 1.0.1: Only proceed with valid tasks
    if (pico_status == pdPASS || autosar_status == pdPASS) {
        vTaskStartScheduler();
    }
}

