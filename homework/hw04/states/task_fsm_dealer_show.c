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
     EventBits_t active_events = 0;
     screen_data_t screen_data;
 
 
     /* Suppress warning for unused parameter */
     (void)param;
 
     while(1)
     {
         if(state_active)
         {
             // clear all bits
             active_events = xEventGroupClearBits(eg_UI, EVENT_UI_SW1 | EVENT_UI_SW2 | EVENT_UI_IO_EXP_INT | EVENT_UI_JOY_UP | EVENT_UI_JOY_DOWN);
 
             // wait for event group notification
             active_events = xEventGroupWaitBits(eg_UI,
                 EVENT_UI_SW2,
                 pdTRUE,
                 pdFALSE,
                 portMAX_DELAY);
 
             // if SW2 pressed, transition
             if(active_events & EVENT_UI_SW2) {
                 // transition to player hit
                 task_print_info("SW2 Pressed, allow player to take cards");
                 xTaskNotifyGive(Task_Handle_FSM_HIT);
                 state_active = false;
             }
 
         }
         else
         {
             // wait for task notification
             ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
 
             // set state active
             state_active = true;
 
             // print message
             task_print_info("Current State: FSM_DEALER_SHOW");
 
             // take the semaphore
             if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
             {
 
                 // get the first two cards for the dealer's hand
                 hand_add_card(Game_Info.dealer_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]);
                 Game_Info.deck->card_index++;
                 hand_add_card(Game_Info.dealer_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]);
                 Game_Info.deck->card_index++;
 
                 // clear cards
                 screen_data.cmd = SCREEN_CMD_CLEAR_CARDS;
                 screen_data.payload.str_ptr = NULL;
                 screen_data.font_color = LCD_COLOR_BLACK;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // draw the first card in dealer's hand
                 screen_data.cmd = SCREEN_CMD_DRAW_CARD;
                 screen_data.payload.card = Game_Info.dealer_hand->cards[0];
                 screen_data.font_color = LCD_COLOR_GREEN;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // draw the back of the second card
                 // set the second card to hidden
                 Game_Info.dealer_hand->cards[1].hidden = true;
                 screen_data.payload.card = Game_Info.dealer_hand->cards[1];
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // give the semaphore
                 xSemaphoreGive(sem_Game_Info);
             }
 
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
 