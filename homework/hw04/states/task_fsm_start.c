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


 extern char APP_DESCRIPTION[];
 extern char APP_MEMBERS[];
 extern char APP_TEAM_NUM[];
 
 TaskHandle_t Task_Handle_FSM_START;
 QueueHandle_t q_eeprom_fsm_start;
 
 /**
  * @brief 
  * This state is used to initialize the game. 
  * 
  * The initialization includes:
  *      - Print the banner with team information to the console 
  *      - Print the high score from the eeprom to the console
  *      - Initialize the player's funds to 1000
  *      - Initialize the initial bet to be 50
  *      - Display the ECE353 Blackjack start screen 
  *
  * You will need to monitor the following events
  *      - EVENT_UI_SW2      
  *          - Transition to state SHUFFLE 
  *      - EVENT_UI_IO_EXP_INT   
  *          - Reset the High Score in the EEPROM to 0.
  * 
  * @param param 
  */
 void task_fsm_start(void *param)
 {
     bool state_active = false;
     EventBits_t events;
     eeprom_msg_t msg;
     uint16_t score;
     screen_data_t screen_data;
 
     /* Suppress warning for unused parameter */
     (void)param;
 
     /* Send the Clear Screen Escape Sequence*/
     task_print("\x1b[2J\x1b[;H");
     task_print("**************************************************\n\r");
     task_print("* %s\n\r", APP_DESCRIPTION);
     task_print("* Date: %s\n\r", __DATE__);
     task_print("* Time: %s\n\r", __TIME__);
     task_print("* %s\n\r", APP_MEMBERS);
     task_print("* %s\n\r", APP_TEAM_NUM);
     task_print("**************************************************\n\r");
 
 
     while(1)
     {
         if(state_active)
         {   

            // clear all bits
            events = xEventGroupClearBits(eg_UI, EVENT_UI_SW1 | EVENT_UI_SW2 | EVENT_UI_IO_EXP_INT | EVENT_UI_JOY_UP | EVENT_UI_JOY_DOWN);
            // wait for even group notification
            events = xEventGroupWaitBits(eg_UI, EVENT_UI_IO_EXP_INT | EVENT_UI_SW2, true, false, portMAX_DELAY);

            // sw2 pressed, shuffle state
             if (events & EVENT_UI_SW2)
             {
                 task_print_info("SW2 pressed");
 
                 xTaskNotifyGive(Task_Handle_FSM_SHUFFLE);
 
                 state_active = false;
             }
 
             // io expander button interrupt, reset eeprom
             if (events & EVENT_UI_IO_EXP_INT)
             {
                 score = 0;
 
                 msg.operation = EEPROM_WRITE;
                 msg.score = score;
                 msg.return_queue = q_eeprom_fsm_start;
             
                 xQueueSend(q_EEPROM, &msg, portMAX_DELAY); 
 
                 task_print_info("Resetting EEPROM data");
             }
         }
         else
         {   
             ulTaskNotifyTake(true, portMAX_DELAY);

             // get the current high score
             // check for new high score
            msg.operation = EEPROM_READ;
            msg.score = 0;
            msg.return_queue = q_eeprom_fsm_start;

            xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
            // high score is now in high_score
            xQueueReceive(q_eeprom_fsm_start, &score, portMAX_DELAY);

            task_print_info("High Score: $%d", score);
 
            task_print_info("Current State: FSM_START");

            if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
            {
                Game_Info.player_funds = 1000;
                Game_Info.player_bet = 50; 
                xSemaphoreGive(sem_Game_Info);
            }


             // draw splash screen, clear screen first
            screen_data.cmd = SCREEN_CMD_CLEAR_ALL;
            screen_data.payload.str_ptr = NULL;
            screen_data.font_color = LCD_COLOR_BLACK;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY); // clear screen

            screen_data.cmd = SCREEN_CMD_DRAW_SPLASH_SCREEN;
            screen_data.font_color = LCD_COLOR_GREEN;
            xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             state_active = true;
         }
     }
 
 }
 
 void task_fsm_start_init(void)
 {
     q_eeprom_fsm_start = xQueueCreate(1, sizeof(eeprom_msg_t));
 
     /* Create the Task */
       xTaskCreate(
       task_fsm_start,
       "Task FSM Start",
       2*configMINIMAL_STACK_SIZE,
       NULL,
       ECE353_TASK_PRIORITY_FSM,
       &Task_Handle_FSM_START);
 }
 