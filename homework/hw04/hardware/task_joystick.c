/**
 * @file task_joystick.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #include "task_joystick.h"

 #if defined(HW04) 
/* Event Groups */
extern EventGroupHandle_t eg_UI;

/**
 * @brief 
 * This function is used to detect when the user presses the joystick UP or DOWN
 * @param pvParameters 
 */
 void task_joystick(void *param)
{
    uint16_t test_num = 0;

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
void task_joystick_init(void)
{
  joystick_init(); 

  // Register the Task with FreeRTOS
  xTaskCreate(
      task_joystick,
      "Task Joystick",
      configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_UI_INPUT,
      NULL);
}
#endif