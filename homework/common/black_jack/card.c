/**
 * @file card.c
 * @author Jake Yun and Hunter Chan
 * @brief 
 * @version 0.1
 * @date 2025-01-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "card.h"
#include "fonts.h"
#include "image.h"
#include "io-lcd.h"
#include <sys/types.h>

/**
 * @brief 
 *  Draws the specified card 
 * @param card 
 */
bool card_draw(card_t *card)
{   
    // check if the card is valid
    bool got_image = false;
    
    // get the image of the card suit
    image_t card_suit;
    got_image = image_get_info(card->suit, &card_suit);

    // check if the image has existing members 
    if (!got_image)
    {
        return false;
    }

    image_t card_value;

    // get the image of the card value
    got_image = font_get_image(card->card_id, &card_value);

    if (card->suit == IMAGE_TYPE_HEART || card->suit == IMAGE_TYPE_DIAMOND)
    {
        card_value.fcolor = LCD_COLOR_RED;
    }

    // check if the image has existing members
    if (!got_image)
    {
        return false;
    }

    // determine the center x coordinate based on the current hand index
    int center_x;

    // determine the position of the card based on the hand index
    switch (card->hand_index)
    {
        case 0: center_x = CARD_VL_X0_CENTER; break;
        case 1: center_x = CARD_VL_X1_CENTER; break;
        case 2: center_x = CARD_VL_X2_CENTER; break;
        case 3: center_x = CARD_VL_X3_CENTER; break;
        case 4: center_x = CARD_VL_X4_CENTER; break;
        case 5: center_x = CARD_VL_X5_CENTER; break;
        case 6: center_x = CARD_VL_X6_CENTER; break;
        default: return false;
    }

    // draw the outer rectangle
    lcd_draw_rectangle(center_x, CARD_X_OUTER_WIDTH, CARD_HL_Y_CENTER, CARD_Y_OUTER_HEIGHT, card->border_color, true);
    
    // draw the innter background rectangle
    lcd_draw_rectangle(center_x, CARD_X_INNER_WIDTH, CARD_HL_Y_CENTER, CARD_Y_INNER_HEIGHT, LCD_COLOR_WHITE, true);
                       
    // draw the suit image at the center 
    lcd_draw_image(center_x, CARD_HL_Y_CENTER, card_suit.width, card_suit.height, card_suit.bitmap, card_suit.fcolor, card_suit.bcolor, true);
    
    // draw the card image at the top left 
    lcd_draw_image(center_x - CARD_VL_X_TEXT_DELTA, CARD_HL_Y_UPPER, card_value.width, card_value.height, card_value.bitmap, card_value.fcolor, card_value.bcolor, true);
    
    // draw the card inmage at the bottom right
    lcd_draw_image(center_x + CARD_VL_X_TEXT_DELTA, CARD_HL_Y_LOWER, card_value.width, card_value.height, card_value.bitmap, card_value.fcolor, card_value.bcolor, true);
    
    return true;
}
