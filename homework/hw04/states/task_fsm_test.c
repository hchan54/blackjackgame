/**
 * @file task_fsm_start.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hw04.h"

extern char APP_DESCRIPTION[];
extern char APP_MEMBERS[];
extern char APP_TEAM_NUM[];

TaskHandle_t Task_Handle_FSM_TEST;
QueueHandle_t q_eeprom_fsm_test;

void task_fsm_test(void *param)
{
    EventBits_t active_events = 0;

    /* Suppress warning for unused parameter */
    (void)param;

    /* Send the Clear Screen Escape Sequence*/
    task_print("\x1b[2J\x1b[;H");
    task_print("**************************************************\n\r");
    task_print("* %s\n\r", "HW04 TEST TASK");
    task_print("* Date: %s\n\r", __DATE__);
    task_print("* Time: %s\n\r", __TIME__);
    task_print("* %s\n\r", APP_MEMBERS);
    task_print("* %s\n\r", APP_TEAM_NUM);
    task_print("**************************************************\n\r");

    while(1)
    {
        /* ADD CODE */
        /* Detect eg_UI events */

       if(active_events & EVENT_UI_SW1)
       {
           task_print_info("SW1 pressed");

       /* ADD CODE */
       /* Write to the IO Expander to turn on the LEDS */
       /* Remember, you will need to send a message to the IO Expander Gate Keeper task */
       /* You cannot directly access hardware resources */
       }

       if(active_events & EVENT_UI_SW2)
       {
           task_print_info("SW2 pressed");
     
           /* ADD CODE */
           
           /* read score from EEPROM */
           /* Remember, you will need to send a message to the EEPROM Gate Keeper task */
           /* You cannot directly access hardware resources */
           
           /* Increment the score read from EEPROM */
           
           /* Write the score score EEPROM */
       }


       if(active_events & EVENT_UI_JOY_DOWN)
       {
            task_print_info("Joystick Moved Down");

           /* ADD CODE */
           /* Remember, you will need to send a message to the LCD Gate Keeper task */
           /* You cannot directly access hardware resources */

            /* Display the test number for the funds, bet, player, and dealer hand */
       }

       if(active_events & EVENT_UI_JOY_UP)
       {
            task_print_info("Joystick Moved Up");

           /* ADD CODE */
           /* Remember, you will need to send a message to the LCD Gate Keeper task */
           /* You cannot directly access hardware resources */

            /* Display the test number for the funds, bet, player, and dealer hand */

       }

       if(active_events & EVENT_UI_IO_EXP_INT)
       {
           task_print_info("U602 pressed");

           /* ADD CODE */
           /* Reset the high score in the EEPROM */
           /* Remember, you will need to send a message to the EEPROM Gate Keeper task */
           /* You cannot directly access hardware resources */
 
       }
    }
}

void task_fsm_test_init(void)
{
    q_eeprom_fsm_test = xQueueCreate(1, sizeof(eeprom_msg_t));

    /* Create the Task */
      xTaskCreate(
      task_fsm_test,
      "Task FSM Test",
      2*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_TEST);
}
