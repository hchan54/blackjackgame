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

 TaskHandle_t Task_Handle_FSM_BET;
 
 /**
  * @brief 
  * This task allows the user to select the amount used for the next bet.  
  * When you enter this state 
  *      - Display the IMAGE_BITMAP_BET_SCREEN in the center of the screen.
  *      - Display the Player Funds in Green.
  *      - Display the Player Bet in Green.
  * 
  * You will need to monitor the following events
  *      - EVENT_UI_JOY_DOWN 
  *          - Decreases the bet by $50.  
  *          - Cannot decrease the bet to a value lower than $50
  *          - Update the LCD with the bet value
  *      - EVENT_UI_JOY_UP   
  *          - Increases the bet by $50.  
  *          - Cannot increase the bet to a value larger than the player funds 
  *          - Update the LCD with the bet value
  *      - EVENT_UI_SW1      
  *          - Transitions the FSM to DEALER SHOW 
  * @param param 
  */
 void task_fsm_bet(void *param)
 {
     bool state_active = false;
     EventBits_t active_events = 0;
     screen_data_t screen_data;
     u_int32_t bet;
     u_int32_t funds;
 
 
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
                 EVENT_UI_SW1 | EVENT_UI_JOY_UP | EVENT_UI_JOY_DOWN,
                 pdTRUE,
                 pdFALSE,
                 portMAX_DELAY);
             
             
             if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
                 // get the player bet
                 bet = Game_Info.player_bet;
                 // get the player funds
                 funds = Game_Info.player_funds;
                 // give semaphore
                 xSemaphoreGive(sem_Game_Info);
             }
 
 
 
             if(active_events & EVENT_UI_SW1) {
                 // transition to dealer show
                 task_print_info("SW1 Pressed, move on to game");
                 xTaskNotifyGive(Task_Handle_FSM_DEALER_SHOW);
                 state_active = false;
             }
 
             // joystick down
             if(active_events & EVENT_UI_JOY_DOWN) {
                 // decrease bet by $50
                 if (bet > 50) {
                     if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
                         Game_Info.player_bet -= 50;
                         // give semaphore
                         xSemaphoreGive(sem_Game_Info);
                     }
                     // update LCD with new bet value
                     screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
                     screen_data.payload.bet = Game_Info.player_bet;
                     screen_data.font_color = LCD_COLOR_GREEN;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                 }
             }
 
             // joystick up
             if(active_events & EVENT_UI_JOY_UP) {
                 // increase bet by $50
                 if (bet < funds) {
                     if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE) {
                         Game_Info.player_bet += 50;
                         // give semaphore
                         xSemaphoreGive(sem_Game_Info);
                     }
                     // update LCD with new bet value
                     screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
                     screen_data.payload.bet = Game_Info.player_bet;
                     screen_data.font_color = LCD_COLOR_GREEN;
                     xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
                 }
             }
         }
         else
         {
             // wait for task notification
             ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
             // set state active
             state_active = true;
             // print message
             task_print_info("Current State: FSM_BET");
 
             // clear the screen
             screen_data.cmd = SCREEN_CMD_CLEAR_ALL;
             screen_data.payload.str_ptr = NULL;
             screen_data.font_color = LCD_COLOR_BLACK;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // display bet screen and players stats
             // bet screen command
             screen_data.cmd = SCREEN_CMD_DRAW_BET_SCREEN;
             // take semaphore
             if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
             {
                 if (Game_Info.player_bet > Game_Info.player_funds)
                 {
                     Game_Info.player_bet = Game_Info.player_funds;
                 }
                 screen_data.payload.bet = Game_Info.player_bet;
                 // give semaphore
                 xSemaphoreGive(sem_Game_Info);
             }
             screen_data.font_color = LCD_COLOR_GREEN;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // display player bet
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // display player funds
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
             // take semaphore
             if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
             {
                 screen_data.payload.funds = Game_Info.player_funds;
                 // give semaphore
                 xSemaphoreGive(sem_Game_Info);
             }
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // reset the player hand and dealer hand and total values
             if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
             {
                 Game_Info.player_hand->num_cards = 0;
                 Game_Info.player_hand->total = 0;
                 Game_Info.dealer_hand->num_cards = 0;
                 Game_Info.dealer_hand->total = 0;
                 // give semaphore
                 xSemaphoreGive(sem_Game_Info);
             }
 
         }
     }
 
 }
 
 void task_fsm_bet_init(void)
 {
     /* Create the Task */
       xTaskCreate(
       task_fsm_bet,
       "Task FSM BET",
       5*configMINIMAL_STACK_SIZE,
       NULL,
       ECE353_TASK_PRIORITY_FSM,
       &Task_Handle_FSM_BET);
 }
 