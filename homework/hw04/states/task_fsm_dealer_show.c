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

TaskHandle_t Task_Handle_FSM_DEALER_SHOW;

/**
 * @brief 
 * This task displays the dealers hand to the user.  
 *
 * The first card should be visible to the user.
 *
 * The second card should be hidden from the user (Blue boarder, grey inner rectangle) 
 * 
 * You will need to monitor the following events
 *      - EVENT_UI_SW2      
 *          - Transitions the FSM to PLAYER HIT
 * @param param 
 */
void task_fsm_dealer_show(void *param)
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

void task_fsm_dealer_show_init(void)
{
    /* Create the Task */
      xTaskCreate(
      task_fsm_dealer_show,
      "Task FSM DEALER SHOW",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_DEALER_SHOW);
}
