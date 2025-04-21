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
#include "task_console.h"

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
    
      // variables for rising edge detection 
      bool sw1_prev, sw2_prev; 
      uint32_t button_value = 0;

      /* Repeatedly running part of the task */
      for (;;)
      {
        /* ADD CODE */
        vTaskDelay(pdMS_TO_TICKS(50)); // 50 ms task delay

        button_value = REG_PUSH_BUTTON_IN;  

        // read in current
        bool sw1_curr = ((button_value & SW1_MASK) == 0); 
        bool sw2_curr = ((button_value & SW2_MASK) == 0);
         
        if (sw1_prev && !sw1_curr) // falling edge detection
        {
            xEventGroupSetBits(eg_UI, EVENT_UI_SW1); 
        }

        if (sw2_prev && !sw2_curr)
        {
            xEventGroupSetBits(eg_UI, EVENT_UI_SW2);
        }

        // update previous button states
        sw1_prev = sw1_curr;
        sw2_prev = sw2_curr;
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
