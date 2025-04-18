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

TaskHandle_t Task_Handle_FSM_HIT;

/**
 * @brief 
 * This task allows the user to take additional cards.  
 * When you enter this state 
 *      - Display the Player Funds in Green.
 *      - Display the Player Bet in Green.
 *      - Display the Player's cards (all visible) 
 *      - Display the Player's hand total (sum up the value of the current hand) 
 * 
 * You will need to monitor the following events
 *      - EVENT_UI_SW1      
 *          - Add a card to the hand
 *          - Display the card on the LCD
 *          - Display the Player's hand total (sum up the value of the current hand) 
 *          - Determine if the Player's hand is equal to 21
 *              - Transition to FSM DEALER HIT
 *          - Determine if the Player's hand is greater than 21
 *              - Transition to FSM HAND COMPLETE 
 *      - EVENT_UI_SW2      
 *          - Transition to FSM DEALER HIT
 * @param param 
 */
void task_fsm_hit(void *param)
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

void task_fsm_hit_init(void)
{
    /* Create the Task */
      xTaskCreate(
      task_fsm_hit,
      "Task FSM HIT",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_HIT);
}
