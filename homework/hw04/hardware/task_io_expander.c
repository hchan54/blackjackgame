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

void hw04_handler_io_exp(void *callback_arg, cyhal_gpio_event_t event);

QueueHandle_t q_IO_Exp;

/**
 * @brief 
 * Handler used to inform non-isr code that a the IO expander push button has been pressed
 * @param callback_arg 
 * @param event 
 */
 void hw04_handler_io_exp(void *callback_arg, cyhal_gpio_event_t event)
 {
    /* ADD CODE */
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

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* ADD CODE */
    }
}

void task_io_expander_init(void)
{
    i2c_init();

    q_IO_Exp = xQueueCreate(1, sizeof(uint8_t));

    /* Enable interrupts from the IO expander on the PSoC6*/
    /* ADD CODE */

    xTaskCreate(
        task_io_expander,
        "Task IO Exp",
        configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_INPUT,
        NULL);
}

#endif
