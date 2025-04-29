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
 
 u_int16_t high_score = 0;
 
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
     screen_data_t screen_data;
     u_int8_t win_streak = 0;
     eeprom_msg_t msg;
 
 
 
     while(1)
     {
         // wait for task notification
         ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
 
         // print scores to console
         task_print_info("Current State: FSM_HAND_COMPLETE");
         if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
             
             task_print_info("P: %d D: %d", Game_Info.player_hand->total, Game_Info.dealer_hand->total);
 
             // compare player hand value to dealer hand value
             if ((Game_Info.player_hand->total > Game_Info.dealer_hand->total && Game_Info.player_hand->total <= 21) || Game_Info.dealer_hand->total > 21) {
                 // player wins
                 Game_Info.player_funds += Game_Info.player_bet;
                 // display the new funds
                 screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                 screen_data.payload.funds = Game_Info.player_funds;
                 screen_data.font_color = LCD_COLOR_GREEN;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // print Win message
                 screen_data.cmd = SCREEN_CMD_DRAW_HAND_STATUS;
                 screen_data.payload.str_ptr = WIN;
                 screen_data.font_color = LCD_COLOR_GREEN;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // blink the player funds
                 for (int i = 0; i < 4; i++) {
                     // clear the screen
                     screen_data.cmd = SCREEN_CMD_CLEAR_STATS;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                     vTaskDelay(pdMS_TO_TICKS(250));
 
                     // draw the player funds
                     screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                     screen_data.payload.funds = Game_Info.player_funds;
                     screen_data.font_color = LCD_COLOR_GREEN;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                     vTaskDelay(pdMS_TO_TICKS(250));
                 }
 
                 // send data to io expander
                 win_streak++;
                 if (win_streak > 7) { // if all LEDs are on, turn them off
                     win_streak = 0;
                 }
                 xQueueSend(q_IO_Exp, &win_streak, portMAX_DELAY);
 
             // player lost case
             } else if ((Game_Info.player_hand->total < Game_Info.dealer_hand->total && Game_Info.dealer_hand->total <= 21) || Game_Info.player_hand->total > 21) {
                 // draw new funds to screen
                 Game_Info.player_funds -= Game_Info.player_bet;
                 screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                 screen_data.payload.funds = Game_Info.player_funds;
                 screen_data.font_color = LCD_COLOR_RED;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // print lose message
                 screen_data.cmd = SCREEN_CMD_DRAW_HAND_STATUS;
                 screen_data.payload.str_ptr = LOOSE;
                 screen_data.font_color = LCD_COLOR_RED;
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
                 // blink the player funds
                 for (int i = 0; i < 4; i++) {
                     // clear the screen
                     screen_data.cmd = SCREEN_CMD_CLEAR_STATS;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                     vTaskDelay(pdMS_TO_TICKS(250));
 
                     // draw the player funds
                     screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
                     screen_data.payload.funds = Game_Info.player_funds;
                     screen_data.font_color = LCD_COLOR_RED;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                     vTaskDelay(pdMS_TO_TICKS(250));
                 }
 
                 // reset win streak on io expander
                 win_streak = 0;
                 xQueueSend(q_IO_Exp, &win_streak, portMAX_DELAY);
             } 
             // push case (tie)
             else {
                 // print Push message
                 screen_data.cmd = SCREEN_CMD_DRAW_HAND_STATUS;
                 screen_data.payload.str_ptr = PUSH;
                 screen_data.font_color = LCD_COLOR_GRAY;
 
                 xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                 vTaskDelay(pdMS_TO_TICKS(2000));
             }
             xSemaphoreGive(sem_Game_Info);
         }
 
         // check for new high score
         msg.operation = EEPROM_READ;
         msg.score = 0;
         msg.return_queue = q_eeprom_fsm_hand_complete;
         xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
         
         // high score is now in high_score
         xQueueReceive(q_eeprom_fsm_hand_complete, &high_score, portMAX_DELAY);
 
         if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
             // check if score is now a new high score
             if (Game_Info.player_funds > high_score) {
 
                 msg.operation = EEPROM_WRITE;
                 msg.score = Game_Info.player_funds;
                 msg.return_queue = NULL;
     
                 xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
 
                 high_score = Game_Info.player_funds;
             }
             // give semaphore
             xSemaphoreGive(sem_Game_Info);
         }
 
         task_print_info("High Score: $%d", high_score);
     
         
         // check player's funds for next state
         if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
             if (Game_Info.player_funds == 0) {
                 xSemaphoreGive(sem_Game_Info);
                 // player is out of money
                 // transition to start state
                 xTaskNotifyGive(Task_Handle_FSM_START);
             } 
             // check if there are enough cards left in deck
             else if ((52 - Game_Info.deck->card_index) >= 15) {
                 xSemaphoreGive(sem_Game_Info);
                 // transition to bet state
                 xTaskNotifyGive(Task_Handle_FSM_BET);
             } else {
                 xSemaphoreGive(sem_Game_Info);
                 // transition to shuffle state
                 xTaskNotifyGive(Task_Handle_FSM_SHUFFLE);
             }
         }
             
         
     }
 
 }
 
 void task_fsm_hand_complete_init(void)
 {
     /* Create the queue to return the high score */
     q_eeprom_fsm_hand_complete = xQueueCreate(1,sizeof(u_int16_t));
 
     /* Create the Task */
       xTaskCreate(
       task_fsm_hand_complete,
       "Task FSM Hand Complete",
       5*configMINIMAL_STACK_SIZE,
       NULL,
       ECE353_TASK_PRIORITY_FSM,
       &Task_Handle_FSM_HAND_COMPLETE);
 }
 