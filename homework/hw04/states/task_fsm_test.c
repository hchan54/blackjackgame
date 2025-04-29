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
 extern QueueHandle_t q_eeprom_fsm_test;
 
 TaskHandle_t Task_Handle_FSM_TEST;
 //QueueHandle_t q_eeprom_fsm_test;
 
 void task_fsm_test(void *param)
 {
     EventBits_t active_events = 0;
     u_int16_t score = 0;
     eeprom_msg_t msg;
     u_int8_t io_expander_leds = 0;
     u_int8_t test_num = 0;
     screen_data_t screen_data;
 
     /* Suppress warning for unused parameter */
     (void)param;
 
     /* Send the Clear Screen Escape Sequence*/
     task_print("\x1b[2J\x1b[;H");
     task_print("**************************************************\n\r");
     task_print("* %s\n\r", "HW04 TEST TASK");
     task_print("* Date: %s\n\r", __DATE__);
     task_print("* Time: %s\n\r", __TIME__);
     task_print("* %s\n\r", APP_MEMBERS);
     task_print("* %s\n\r", APP_TEAM_NUM);
     task_print("**************************************************\n\r");
 
     while(1)
     {
         /* ADD CODE */
         /* Detect eg_UI events */
         active_events = xEventGroupWaitBits(eg_UI,
                                         EVENT_UI_SW1 | EVENT_UI_SW2 | EVENT_UI_JOY_UP | EVENT_UI_JOY_DOWN | EVENT_UI_IO_EXP_INT,
                                         pdTRUE,
                                         pdFALSE,
                                         portMAX_DELAY);
 
        if(active_events & EVENT_UI_SW1)
        {
            task_print_info("SW1 pressed");
 
            // turn lights on
            io_expander_leds++;
            if (io_expander_leds > 7) { // if all LEDs are on, turn them off
             io_expander_leds = 0;
           }
            xQueueSend(q_IO_Exp, &io_expander_leds, portMAX_DELAY);
 
        /* ADD CODE */
        /* Write to the IO Expander to turn on the LEDS */
        /* Remember, you will need to send a message to the IO Expander Gate Keeper task */
        /* You cannot directly access hardware resources */
        }
 
        if(active_events & EVENT_UI_SW2)
        {
            task_print_info("SW2 pressed");
      
            /* ADD CODE */
            
            /* read score from EEPROM */
 
            // perform a read
            msg.operation = EEPROM_READ;
             msg.score = score;
             msg.return_queue = q_eeprom_fsm_test;
             xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
             xQueueReceive(q_eeprom_fsm_test, &score, portMAX_DELAY);
 
            // print message
            task_print_info("High Score Read: $%d", score);
            /* Remember, you will need to send a message to the EEPROM Gate Keeper task */
            /* You cannot directly access hardware resources */
            
            /* Increment the score read from EEPROM */
             score += 1;
              // write to eeprom
             msg.operation = EEPROM_WRITE;
             msg.score = score;
             
             task_print_info("High Score Written: $%d", score);
            /* Write the score score EEPROM */
            xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
        }
 
 
        if(active_events & EVENT_UI_JOY_DOWN)
        {
             task_print_info("Joystick Moved Down");
 
            /* ADD CODE */
            /* Remember, you will need to send a message to the LCD Gate Keeper task */
            /* You cannot directly access hardware resources */
 
            // decerement test_num
            if (test_num > 0) { test_num--; }
 
            // draw bet
            screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
             screen_data.payload.bet = test_num;
             screen_data.font_color = LCD_COLOR_GREEN;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // draw funds
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
             screen_data.payload.funds = test_num;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // draw player and dealer hand values
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_PLAYER_HAND;
             screen_data.payload.hand_value = test_num;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_DEALER_HAND;
             screen_data.payload.hand_value = test_num;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             /* Display the test number for the funds, bet, player, and dealer hand */
        }
 
        if(active_events & EVENT_UI_JOY_UP)
        {
             task_print_info("Joystick Moved Up");
 
            /* ADD CODE */
            /* Remember, you will need to send a message to the LCD Gate Keeper task */
            /* You cannot directly access hardware resources */
 
            // increment test_num
            test_num++;
            // draw bet value
            screen_data.cmd = SCREEN_CMD_DRAW_STATS_BET;
             screen_data.payload.bet = test_num;
             screen_data.font_color = LCD_COLOR_GREEN;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // draw stats
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_FUNDS;
             screen_data.payload.funds = test_num;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             // draw player and dealer hand values
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_PLAYER_HAND;
             screen_data.payload.hand_value = test_num;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
             screen_data.cmd = SCREEN_CMD_DRAW_STATS_DEALER_HAND;
             screen_data.payload.hand_value = test_num;
             xQueueSend(q_Screen, &screen_data, portMAX_DELAY);
 
 
             /* Display the test number for the funds, bet, player, and dealer hand */
 
        }
 
        if(active_events & EVENT_UI_IO_EXP_INT)
        {
            task_print_info("U602 pressed");
            task_print_info("Resetting EEPROM data");
 
            /* Reset the high score in the EEPROM */
            /* Remember, you will need to send a message to the EEPROM Gate Keeper task */
            /* You cannot directly access hardware resources */
            msg.operation = EEPROM_WRITE;
             msg.score = 0;
             msg.return_queue = q_eeprom_fsm_test;
             
             
            /* Write the score score EEPROM */
            xQueueSend(q_EEPROM, &msg, portMAX_DELAY);
 
 
  
        }
     }
 }
 
 void task_fsm_test_init(void)
 {
     q_eeprom_fsm_test = xQueueCreate(1, sizeof(eeprom_msg_t));
 
     /* Create the Task */
       xTaskCreate(
       task_fsm_test,
       "Task FSM Test",
       2*configMINIMAL_STACK_SIZE,
       NULL,
       ECE353_TASK_PRIORITY_FSM,
       &Task_Handle_FSM_TEST);
 }
 