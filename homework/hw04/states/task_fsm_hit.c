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
     screen_data_t screen_data;
     EventBits_t active_events = 0;
 
 
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
                 EVENT_UI_SW2 | EVENT_UI_SW1,
                 pdTRUE,
                 pdFALSE,
                 portMAX_DELAY);
 
             // if SW1 pressed, add a card to the hand
             if(active_events & EVENT_UI_SW1) {
                 task_print_info("SW1 Pressed, Hit");
                 if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
                     // add a card to the hand
                     hand_add_card(Game_Info.player_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]);
                     Game_Info.deck->card_index++;
 
                     // draw the card
                     screen_data.cmd = SCREEN_CMD_DRAW_CARD;
                     screen_data.payload.card = Game_Info.player_hand->cards[Game_Info.player_hand->num_cards - 1];
                     screen_data.font_color = LCD_COLOR_GREEN;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                     // display the value of player's hand
                     screen_data.cmd = SCREEN_CMD_DRAW_STATS_PLAYER_HAND;
                     screen_data.payload.hand_value = Game_Info.player_hand->total;
                     screen_data.font_color = LCD_COLOR_GREEN;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                     // check for bust or blackjack
                     if(Game_Info.player_hand->total > 21) {
                         // transition to hand complete
                         xTaskNotifyGive(Task_Handle_FSM_HAND_COMPLETE);
                         state_active = false;
                     }
                     else if(Game_Info.player_hand->total == 21) {
                         // delay for one sec
                         vTaskDelay(pdMS_TO_TICKS(1000));
                         // transition to dealer hit
                         xTaskNotifyGive(Task_Handle_FSM_DEALER_HIT);
                         state_active = false;
                     }
 
                     xSemaphoreGive(sem_Game_Info); 
                 }
             }
 
             // if SW2 pressed, transition
             if(active_events & EVENT_UI_SW2) {
                 task_print_info("SW2 Pressed, Stay");
                 // transition to dealer hit
                 xTaskNotifyGive(Task_Handle_FSM_DEALER_HIT);
                 state_active = false;
             }
 
         }
         else
         {
 
             // wait for task notification
             ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
 
             // set state active
             state_active = true;
 
             task_print_info("Current State: FSM HIT");
 
             // clear cards
             screen_data.cmd = SCREEN_CMD_CLEAR_CARDS;
             screen_data.payload.str_ptr = NULL;
             screen_data.font_color = LCD_COLOR_BLACK;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY); // clear screen
 
             if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
             {
                 
                 // display player funds
                 screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                 screen_data.payload.funds = Game_Info.player_funds;
                 screen_data.font_color = LCD_COLOR_GREEN;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // display player bet
                 screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
                 screen_data.payload.bet = Game_Info.player_bet;
                 screen_data.font_color = LCD_COLOR_GREEN;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // add 2 cards to player's hand
                 hand_add_card(Game_Info.player_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]);
                 Game_Info.deck->card_index++;
                 hand_add_card(Game_Info.player_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]);
                 Game_Info.deck->card_index++;
 
                 // draw the first card in player's hand
                 screen_data_t screen_data;
                 screen_data.cmd = SCREEN_CMD_DRAW_CARD;
                 screen_data.payload.card = Game_Info.player_hand->cards[0];
                 screen_data.font_color = LCD_COLOR_GREEN;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // draw the second card
                 screen_data.payload.card = Game_Info.player_hand->cards[1];
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // display the value of player's hand
                 screen_data.cmd = SCREEN_CMD_DRAW_STATS_PLAYER_HAND;
                 screen_data.payload.hand_value = Game_Info.player_hand->total;
                 screen_data.font_color = LCD_COLOR_GREEN;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

                 if(Game_Info.player_hand->total == 21) {
                    // delay for one sec
                    vTaskDelay(pdMS_TO_TICKS(1000));
                    // transition to dealer hit
                    xTaskNotifyGive(Task_Handle_FSM_DEALER_HIT);
                    state_active = false;
                }
 
             xSemaphoreGive(sem_Game_Info);
             }
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
 