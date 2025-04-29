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
     screen_data_t screen_data;
     u_int16_t hand_val;
     
 
     while(1)
     {   
         ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 

        // create the initial screen
        screen_data.cmd = SCREEN_CMD_CLEAR_CARDS;    
        if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
            // get dealer hand value
            screen_data.payload.hand_value = Game_Info.dealer_hand->total;
            xSemaphoreGive(sem_Game_Info);
        }
        screen_data.font_color = LCD_COLOR_RED;
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY); // erase player cards 
        
        screen_data.cmd = SCREEN_CMD_DRAW_STATS_DEALER_HAND;
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY); // display dealer score

        // draw the first card in dealer's hand
        screen_data.cmd = SCREEN_CMD_DRAW_CARD;
        if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
            screen_data.payload.card = Game_Info.dealer_hand->cards[0];
            xSemaphoreGive(sem_Game_Info);
        }
        screen_data.font_color = LCD_COLOR_GREEN;
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

        // draw the second card
        if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
            // set the second card to hidden
            Game_Info.dealer_hand->cards[1].hidden = false;
            screen_data.payload.card = Game_Info.dealer_hand->cards[1];
            xSemaphoreGive(sem_Game_Info);
        }
        xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

 
         // transition to HAND_COMPLETE 
         if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
         {
            // get the hand value
            hand_val = Game_Info.dealer_hand->total;
             // give semaphore
             xSemaphoreGive(sem_Game_Info);
         }
                     
         // repeat dealer drawing while value is under 17
         while (hand_val < 17)
         {
                // add a card to the dealer's hand
                if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
                {
                    // draw a card and update the hand value
                    hand_add_card(Game_Info.dealer_hand, &Game_Info.deck->cards[Game_Info.deck->card_index]);
                    Game_Info.deck->card_index++;
                    hand_val = Game_Info.dealer_hand->total;

                    // draw the card on the screen
                    screen_data.cmd = SCREEN_CMD_DRAW_CARD;
                    screen_data.payload.card = Game_Info.dealer_hand->cards[Game_Info.dealer_hand->num_cards - 1];
                    screen_data.font_color = LCD_COLOR_GREEN;
                    xQueueSend(q_Screen, &screen_data, portMAX_DELAY);

                    xSemaphoreGive(sem_Game_Info);
                }
                
                // display the value of dealer's hand
                screen_data.cmd = SCREEN_CMD_DRAW_STATS_DEALER_HAND;
                screen_data.payload.hand_value = hand_val;
                screen_data.font_color = LCD_COLOR_RED;
                xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                
                vTaskDelay(1000); // 1 second between draws
        }
            
        // move to the HAND_COMPLETE state
        xTaskNotifyGive(Task_Handle_FSM_HAND_COMPLETE);
        
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