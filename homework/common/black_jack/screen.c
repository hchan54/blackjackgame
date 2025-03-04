/**
 * @file screen.c
 * @author Jake Yun and Hunter Chan
 * @brief 
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "screen.h"

/**
 * @brief 
 * Used to update the player funds on the LCD
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_funds(int16_t funds, uint16_t fcolor) {
    // define string as a char array
    char funds_str[6] = {'F','u','n','d','s',':'};

    // base x position
    int x_position = LOC_TEXT_COL_1_X;

    // loop through the funds string and display each character
    for (int i = 0; i < 6; i++) {
        // get the image of the character
        image_t char_image;
        font_get_image(funds_str[i], &char_image);

        // draw the rectangle around the character
        lcd_draw_rectangle(x_position, char_image.width + 4, LOC_TEXT_ROW_1_Y, \
            char_image.height + 4, LCD_COLOR_BLACK, false);

        // draw the character
        lcd_draw_image(x_position, LOC_TEXT_ROW_1_Y, char_image.width, \
            char_image.height, char_image.bitmap, fcolor, LCD_COLOR_BLACK, false);

        // increment the x position
        x_position += char_image.width + 2;
    }

    // convert the funds to a string
    char funds_val[10];
    sprintf(funds_val, "$%d", funds);

    // set the x position to the start of the funds value
    x_position = LOC_TEXT_COL_2_X;

    // loop through each char of funds and display a rectangle and the char
    for (int i = 0; i < strlen(funds_val); i++) {
        image_t char_image;
        font_get_image(funds_val[i], &char_image);

        lcd_draw_rectangle(LOC_TEXT_COL_2_X + i*FONT_PIXELS_WIDTH, char_image.width + 4, LOC_TEXT_ROW_1_Y, \
            char_image.height + 4, LCD_COLOR_BLACK, false);

        lcd_draw_image(x_position, LOC_TEXT_ROW_1_Y, char_image.width, \
            char_image.height, char_image.bitmap, fcolor, LCD_COLOR_BLACK, false);

        x_position += char_image.width + 2;
    }
}

/**
 * @brief 
 * Used to update the player bet on the LCD
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_bet(int16_t bet, uint16_t fcolor)
{
    // define string as a char array
    char bet_str[4] = {'B','e','t',':'};

    // base x position
    int x_position = LOC_TEXT_COL_1_X;

    // loop through the bet string and display each character
    for (int i = 0; i < 4; i++) {
        // get the image of the character
        image_t char_image;
        font_get_image(bet_str[i], &char_image);

        // draw the rectangle around the character
        lcd_draw_rectangle(x_position, char_image.width + 4, LOC_TEXT_ROW_2_Y, \
            char_image.height + 4, LCD_COLOR_BLACK, false);

        // draw the character
        lcd_draw_image(x_position, LOC_TEXT_ROW_2_Y, char_image.width, \
            char_image.height, char_image.bitmap, fcolor, LCD_COLOR_BLACK, false);

        // increment the x position
        x_position += char_image.width + 2;
    }

    // convert the bet to a string
    char bet_val[10];
    sprintf(bet_val, "$%d", bet);

    // set the x position to the start of the bet value
    x_position = LOC_TEXT_COL_2_X;

    // loop through each char of bet and display a rectangle and the char
    for (int i = 0; i < strlen(bet_val); i++) {
        image_t char_image;
        font_get_image(bet_val[i], &char_image);

        lcd_draw_rectangle(x_position, char_image.width + 4, LOC_TEXT_ROW_2_Y, \
            char_image.height + 4, LCD_COLOR_BLACK, false);

        lcd_draw_image(x_position, LOC_TEXT_ROW_2_Y, char_image.width, \
            char_image.height, char_image.bitmap, fcolor, LCD_COLOR_BLACK, false);

        x_position += char_image.width + 2;
    }
}

/**
 * @brief 
 * Used to update the total of the dealer's hand
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_dealer_hand(int16_t hand_value, uint16_t fcolor) {
    // convert the hand value to a string
    char dealer_val[10];
    sprintf(dealer_val, "%d", hand_value);

    int x_position = LOC_TEXT_COL_3_X;

    // loop through each char of the dealer's hand and display a rectangle and the char
    for (int i = 0; i < strlen(dealer_val); i++) {
        image_t char_image;
        font_get_image(dealer_val[i], &char_image);

        lcd_draw_rectangle(x_position, char_image.width + 4, LOC_TEXT_ROW_2_Y, \
            char_image.height + 4, LCD_COLOR_BLACK, false);

        lcd_draw_image(x_position, LOC_TEXT_ROW_2_Y, char_image.width, \
            char_image.height, char_image.bitmap, fcolor, LCD_COLOR_BLACK, false);

        x_position += char_image.width + 2;
    }
}

/**
 * @brief 
 * Used to update the total of the player's hand
 * @param game_stats
 * Contains the current game stats 
 */
void screen_display_stats_player_hand(int16_t hand_value, uint16_t fcolor) {
    // convert the hand value to a string
    char player_val[10];
    sprintf(player_val, "%d", hand_value);

    int x_position = LOC_TEXT_COL_3_X;

    // loop through each char of the player's hand and display a rectangle and the char
    for (int i = 0; i < strlen(player_val); i++) {
        image_t char_image;
        font_get_image(player_val[i], &char_image);

        lcd_draw_rectangle(x_position, char_image.width + 16, LOC_TEXT_ROW_1_Y, \
            char_image.height + 4, LCD_COLOR_BLACK, false);

        lcd_draw_image(x_position, LOC_TEXT_ROW_1_Y, char_image.width, \
            char_image.height, char_image.bitmap, fcolor, LCD_COLOR_BLACK, false);

        x_position += char_image.width + 2;
    }
}