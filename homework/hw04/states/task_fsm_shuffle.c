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

TaskHandle_t Task_Handle_FSM_SHUFFLE;


/**
 * @brief 
 * This state is used to shuffle the deck of cards.  After the deck has been shuffled, an unconditional transition is 
 * made to the BET state. 
 * @param param 
 */
void task_fsm_shuffle(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    while(1)
    {
    }

}

void task_fsm_shuffle_init(void)
{
    /* Create the Task */
      xTaskCreate(
      task_fsm_shuffle,
      "Task FSM Shuffle",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_SHUFFLE);
}
