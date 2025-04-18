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

TaskHandle_t Task_Handle_FSM_START;
QueueHandle_t q_eeprom_fsm_start;

/**
 * @brief 
 * This state is used to initialize the game. 
 * 
 * The initialization includes:
 *      - Print the banner with team information to the console 
 *      - Print the high score from the eeprom to the console
 *      - Initialize the player's funds to 1000
 *      - Initialize the initial bet to be 50
 *      - Display the ECE353 Blackjack start screen 
 *
 * You will need to monitor the following events
 *      - EVENT_UI_SW2      
 *          - Transition to state SHUFFLE 
 *      - EVENT_UI_IO_EXP_INT   
 *          - Reset the High Score in the EEPROM to 0.
 * 
 * @param param 
 */
void task_fsm_start(void *param)
{
    bool state_active = false;

    /* Suppress warning for unused parameter */
    (void)param;

    /* Send the Clear Screen Escape Sequence*/
    task_print("\x1b[2J\x1b[;H");
    task_print("**************************************************\n\r");
    task_print("* %s\n\r", APP_DESCRIPTION);
    task_print("* Date: %s\n\r", __DATE__);
    task_print("* Time: %s\n\r", __TIME__);
    task_print("* %s\n\r", APP_MEMBERS);
    task_print("* %s\n\r", APP_TEAM_NUM);
    task_print("**************************************************\n\r");

    while(1)
    {
        if(state_active)
        {
        }
        else
        {
        }
    }

}

void task_fsm_start_init(void)
{
    q_eeprom_fsm_start = xQueueCreate(1, sizeof(eeprom_msg_t));

    /* Create the Task */
      xTaskCreate(
      task_fsm_start,
      "Task FSM Start",
      2*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_START);
}
