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

TaskHandle_t Task_Handle_FSM_BET;

/**
 * @brief 
 * This task allows the user to select the amount used for the next bet.  
 * When you enter this state 
 *      - Display the IMAGE_BITMAP_BET_SCREEN in the center of the screen.
 *      - Display the Player Funds in Green.
 *      - Display the Player Bet in Green.
 * 
 * You will need to monitor the following events
 *      - EVENT_UI_JOY_DOWN 
 *          - Decreases the bet by $50.  
 *          - Cannot decrease the bet to a value lower than $50
 *          - Update the LCD with the bet value
 *      - EVENT_UI_JOY_UP   
 *          - Increases the bet by $50.  
 *          - Cannot increase the bet to a value larger than the player funds 
 *          - Update the LCD with the bet value
 *      - EVENT_UI_SW1      
 *          - Transitions the FSM to DEALER SHOW 
 * @param param 
 */
void task_fsm_bet(void *param)
{
    bool state_active = false;

    /* Suppress warning for unused parameter */
    (void)param;

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

void task_fsm_bet_init(void)
{
    /* Create the Task */
      xTaskCreate(
      task_fsm_bet,
      "Task FSM BET",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_BET);
}
