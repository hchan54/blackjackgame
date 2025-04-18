/**
 * @file task_fsm_dealer_hit.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hw04.h"

TaskHandle_t Task_Handle_FSM_DEALER_HIT;

/**
 * @brief 
 * This task draws cards for the dealers hand 
 * When you enter this state 
 *      - Display the Player Funds in Green
 *      - Display the Player Bet in Green
 *      - Erase the Player's cards
 *      - Add/display cards to the Dealer's hand
 *      - Update the Dealer's hand total for each card added
 *      - Delay 1 second between drawing cards 
 *      - Continue to add cards to the Dealer's hand until the total
 *        of the Dealer's hand is greater than OR equal to 17 
 *      - When the Dealer's hand is greater than or equal to 17, 
 *        transition to HAND_COMPLETE
 * @param param 
 */
void task_fsm_dealer_hit(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    while(1)
    {
    }

}

void task_fsm_dealer_hit_init(void)
{
    /* Create the Task */
      xTaskCreate(
      task_fsm_dealer_hit,
      "Task FSM Dealer Hit",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_DEALER_HIT);
}