/**
 * @file task_io_expander.c
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "task_io_expander.h"

#if defined(HW04) 

/* Event Groups */
extern EventGroupHandle_t eg_UI;

QueueHandle_t q_IO_Exp;


/**
 * @brief 
 * Handler used to inform non-isr code that a the IO expander push button has been pressed
 * @param callback_arg 
 * @param event 
 */
 void hw04_handler_io_exp(void *callback_arg, cyhal_gpio_event_t event)
 {
    bool button_pressed = false;

    // check if it is a falling edge
    if (event == CYHAL_GPIO_IRQ_FALL) {
        // if the button was not pressed before then set the bits
        if (!button_pressed) {
            button_pressed = true;
            xEventGroupSetBitsFromISR(eg_UI, EVENT_UI_IO_EXP_INT, NULL);
        }
    } else if (event == CYHAL_GPIO_IRQ_RISE) {
        button_pressed = false;
    }
 }

/**
 * @brief 
 * Displays the number of whammies that have been selected
 * @param param 
 * Not Used
 */
void task_io_expander(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;
    uint8_t light;

    for (;;)
    {
        // wait for a message in queue
        xQueueReceive(q_IO_Exp, &light, portMAX_DELAY);

        // active high LEDs so we mask bits with LED_count
        uint8_t led_mask = (1 << light) - 1;
        // set the io expander
        io_expander_set_output_port(led_mask);

    }
}

void task_io_expander_init(void)
{
    i2c_init();

    q_IO_Exp = xQueueCreate(1, sizeof(uint8_t));

    /* Enable interrupts from the IO expander on the PSoC6*/
    io_expander_enable_int();

    xTaskCreate(
        task_io_expander,
        "Task IO Exp",
        configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_INPUT,
        NULL);
}

#endif
