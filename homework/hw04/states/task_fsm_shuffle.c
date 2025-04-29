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
         // wait for task notification
         ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
 
         if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
         {
             // initialize the deck
             deck_init(Game_Info.deck);
             // shuffle the deck
             deck_randomize(Game_Info.deck);
             // give the semaphore
             xSemaphoreGive(sem_Game_Info);
         }
 
         
         // print message
         task_print_info("Current State: FSM_SHUFFLE");
 
         // transition to betting state
         xTaskNotifyGive(Task_Handle_FSM_BET);
 
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
 