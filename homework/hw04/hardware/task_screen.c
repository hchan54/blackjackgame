/**
 * @file task_lcd_game_stats.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "task_screen.h"
#if defined(HW04)

QueueHandle_t q_Screen;

/******************************************************************************
 * FreeRTOS Related Functions
 ******************************************************************************/

/**
 * @brief
 * @param param
 */
void task_screen(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;
    screen_data_t screen_data;

    /* Repeatedly running part of the task */
    for (;;)
    {
        xQueueReceive(q_Screen, &screen_data, portMAX_DELAY);
        // check the command
        switch(screen_data.cmd)
        {
            case SCREEN_CMD_CLEAR_ALL:
            {
                // clear the whole screen
                lcd_clear_screen(LCD_COLOR_BLACK);
                break;
            }
            case SCREEN_CMD_CLEAR_CARDS:
            {
                // draw a black rectangle to cover cards
                lcd_draw_rectangle(0, 320, 85, 150, LCD_COLOR_BLACK, false);
                break;
            }
            case SCREEN_CMD_CLEAR_STATS:
            {
                // draw rectangle to cover funds
                lcd_draw_rectangle(LOC_TEXT_COL_1_X, 250, LOC_TEXT_ROW_1_Y, 42, LCD_COLOR_BLACK, false);
                // draw rectangle to cover bet (not needed)
                // lcd_draw_rectangle(LOC_TEXT_COL_1_X, 250, LOC_TEXT_ROW_2_Y, 42, LCD_COLOR_BLACK, false);
                break;
            }
            case SCREEN_CMD_DRAW_CARD:
            {
                // draw card to screen
                card_draw(&screen_data.payload.card);
                break;
            }
            case SCREEN_CMD_DRAW_STATS_FUNDS:
            {
                // display funds
                screen_display_stats_funds( screen_data.payload.funds,
                                            screen_data.font_color);
                break;
            }
            case SCREEN_CMD_DRAW_STATS_BET:
            {
                // display bet
                screen_display_stats_bet( screen_data.payload.bet,
                                          screen_data.font_color);
                break;
            }
            case SCREEN_CMD_DRAW_STATS_DEALER_HAND:
            {
                // display hand value, assumes dealer hand is in payload
                screen_display_stats_dealer_hand( screen_data.payload.hand_value,
                                                  screen_data.font_color);
                break;
            }
            case SCREEN_CMD_DRAW_STATS_PLAYER_HAND:
            {
                // display hand value, assumes player hand is in payload
                screen_display_stats_player_hand( screen_data.payload.hand_value,
                                                  screen_data.font_color);
                break;
            }
            case SCREEN_CMD_DRAW_STATS_ALL:
            {
                // take semaphore
                if (xSemaphoreTake(sem_Game_Info, portMAX_DELAY) == pdTRUE)
                {
                    // draw the player funds
                    screen_display_stats_funds( Game_Info.player_funds,
                                                screen_data.font_color);
                    // draw the player bet
                    screen_display_stats_bet( Game_Info.player_bet,
                                              screen_data.font_color);
                    // draw the dealer hand value
                    screen_display_stats_dealer_hand( Game_Info.dealer_hand->total,
                                                      screen_data.font_color);
                    // draw the player hand value
                    screen_display_stats_player_hand( Game_Info.player_hand->total,
                                                      screen_data.font_color);
                    // give semaphore
                    xSemaphoreGive(sem_Game_Info);
                }
                break;
            }
            case SCREEN_CMD_DRAW_SPLASH_SCREEN:
            {
                // create image and draw image of splash screen
                image_t splash_screen;
                image_get_info(IMAGE_TYPE_START_SCREEN, &splash_screen);
                lcd_draw_image(160, 120, splash_screen.width, splash_screen.height, splash_screen.bitmap, splash_screen.fcolor, splash_screen.bcolor, true);
                break;
            }
            case SCREEN_CMD_DRAW_BET_SCREEN:
            {
                // create image and draw image of bet screen
                image_t bet_screen;
                image_get_info(IMAGE_TYPE_BET_SCREEN, &bet_screen);
                lcd_draw_image(120, 160, bet_screen.width, bet_screen.height, bet_screen.bitmap, bet_screen.fcolor, bet_screen.bcolor, true);
                break;
            }
            case SCREEN_CMD_DRAW_HAND_STATUS:
            {
                // get the string to print
                char* str = screen_data.payload.str_ptr;

                // get font color
                uint16_t fcolor = screen_data.font_color;

                // base x position
                int x_position = LOC_HAND_STATUS_X;

                // loop through the each char in string
                for (int i = 0; i < strlen(str); i++) {
                    // get the image of the character
                    image_t char_image;
                    font_get_image(str[i], &char_image);

                    // draw the rectangle around the character
                    lcd_draw_rectangle(x_position - 2, char_image.width + 4, LOC_HAND_STATUS_Y, \
                        char_image.height + 4, LCD_COLOR_BLACK, false);

                    // draw the character
                    lcd_draw_image(x_position, LOC_HAND_STATUS_Y, char_image.width, \
                        char_image.height, char_image.bitmap, fcolor, LCD_COLOR_BLACK, false);

                    // increment the x position
                    x_position += char_image.width + 2;
                }
                
                break;
            }
            

        }
    }
}

void task_screen_init(void)
{
    /* Initialize the LCD hardware */
    ece353_enable_lcd();

    /* Create LCD Queues */
    q_Screen = xQueueCreate(1, sizeof(screen_data_t));

    xTaskCreate(
        task_screen,
        "Task Screen",
        10 * configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_OUTPUT,
        NULL);
}

#endif