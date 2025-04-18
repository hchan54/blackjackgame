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

TaskHandle_t Task_Handle_FSM_HAND_COMPLETE;
QueueHandle_t q_eeprom_fsm_hand_complete;

char WIN[] = "Win!";
char PUSH[] = "Push";
char LOOSE[] = "Loose";

/**
 * @brief 
 * This task determines if the user wins or looses the current hand.
 *
 * If the players wins
 *      - Add the bet amount to the player funds
 *      - Display the player funds in Green
 *      - Print "Win!" Green to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y 
 *      - Blink the Player Funds On/Off 4 times.  
 *      - Use a delay of 250mS between blinking On/Off
 *      - Display the player's current win streak on the IO Expander 
 *
 * If the players looses 
 *      - Subtract the bet amount to the player funds
 *      - Display the player funds in Red 
 *      - Print "Loose" in Red to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y 
 *      - Blink the Player Funds On/Off 4 times.  
 *      - Use a delay of 250mS between blinking On/Off
 *      - Set the player's current win streak to 0 and update the IO Expander 
 *
 * If the players pushes (tie)
 *      - Print "Push" in Grey to the LCD screen at LOC_HAND_STATUS_X, LOC_HAND_STATUS_Y 
 *      - Delay for 2 seconds
 *
 * In all situations
 *      - Check to see if a new high score for the player funds. Write new high scores to the EEPROM.
 *      - If the player funds is equal to 0, transition to the START state.
 *      - If the player funds are greater than 0, check to see if the remaining cards in the deck are greater than 15
 *          - If greater than or equal to 15, transition to the BET state
 *          - If less than 15, transition to the SHUFFLE state
 * @param param 
 */
void task_fsm_hand_complete(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    while(1)
    {
    }

}

void task_fsm_hand_complete_init(void)
{
    /* Create the queue to return the high score */
    q_eeprom_fsm_hand_complete = xQueueCreate(1,sizeof(eeprom_msg_t));

    /* Create the Task */
      xTaskCreate(
      task_fsm_hand_complete,
      "Task FSM Hand Complete",
      5*configMINIMAL_STACK_SIZE,
      NULL,
      ECE353_TASK_PRIORITY_FSM,
      &Task_Handle_FSM_HAND_COMPLETE);
}
