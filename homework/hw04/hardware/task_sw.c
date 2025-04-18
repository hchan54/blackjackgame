/**
 * @file task_sw.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "task_sw.h"

#if defined(HW04)

/* Event Groups */
extern EventGroupHandle_t eg_UI;

/**
 * @brief
 * Function used to detect when SW1, SW2, and SW3 are been pressed.  
 * The task should detect the initial button press by debouncing 
 * the push button for 50mS.  Pressing the button for longer than 50mS 
 * should only result in a single button event.
 * 
 * @param param
 *  Unused
 */
void task_switches(void *param)
{
      /* Suppress warning for unused parameter */
      (void)param;

      /* Repeatedly running part of the task */
      for (;;)
      {
          /* ADD CODE */
      }
}

/**
 * @brief
 * Initializes User Push Buttons and creates the corresponding FreeRTOS tasks for SW1 and SW2
 */
void task_sw_init(void)
{
  push_buttons_init(false);

  // Register the Task with FreeRTOS
  xTaskCreate(
      task_switches,
      "Task Switches",
      configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_UI_INPUT,
      NULL);
}

#endif
