/**
 * @file task_lcd_game_stats.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #include "task_screen.h"
#if defined(HW04)

QueueHandle_t q_Screen;

/******************************************************************************
 * FreeRTOS Related Functions
 ******************************************************************************/

/**
 * @brief
 * @param param
 */
void task_screen(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* ADD CODE */
    }
}

void task_screen_init(void)
{
    /* Initialize the LCD hardware */
    ece353_enable_lcd();

    /* Create LCD Queues */
    q_Screen = xQueueCreate(1, sizeof(screen_data_t));

    xTaskCreate(
        task_screen,
        "Task Screen",
        10 * configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_OUTPUT,
        NULL);
}

#endif