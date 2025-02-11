/**
 * @file hw01.c
 * @author Jake Yun and Hunter Chan
 * @brief 
 * @version 0.1
 * @date 2025-01-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "hw01.h"
#include "card.h"
#include "console.h"
#include "cyhal_system.h"
#include "image.h"
#include "io-lcd.h"
#include "screen.h"

#if defined(HW01)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW01";
char STUDENTS[] = "Jake Yun and Hunter Chan";     /* Modify */
char TEAM[] = "Team13";                 /* Modify */

cyhal_trng_t trng_obj;


/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{
    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);

    /* Enable the push buttons*/
    push_buttons_init(false);

    ece353_enable_lcd();

    console_init();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 */
void main_app(void)
{
    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Team:%s\n\r", TEAM);
    printf("* Names:%s\n\r", STUDENTS);
    printf("**************************************************\n\r");

    // define the first card and draw it
    card_t my_card = {
        .border_color = LCD_COLOR_BLUE,
        .suit = IMAGE_TYPE_CLUB,
        .card_id = CARD_ID_2,
        .hand_index = 0
    };

    card_draw(&my_card);

    // define some local variables that will be incremented
    int funds = 0;
    int bet = 50;
    int num_of_cards = 0;
    int hand_index_counter = 0; // used to figure out the hand index of the card
    bool sw1_pressed = false;
    u_int32_t reg_val; // value read in to check if SW1 is pressed
    int hand_index;
    image_type_t suit;
    card_id_t value;

    // display the initial stats
    screen_display_stats_funds(funds, LCD_COLOR_GREEN);

    screen_display_stats_bet(bet, LCD_COLOR_GREEN);

    screen_display_stats_player_hand(21, LCD_COLOR_GREEN);

    screen_display_stats_dealer_hand(19, LCD_COLOR_RED);

    // array of const for the card values
    const card_id_t value_map[] = {CARD_ID_2, CARD_ID_3, CARD_ID_4, CARD_ID_5,
                                  CARD_ID_6, CARD_ID_7, CARD_ID_8, CARD_ID_9,
                                  CARD_ID_10, CARD_ID_J, CARD_ID_Q, CARD_ID_K, CARD_ID_A};

    // Every 250 mS, detect if SW1 is being pressed
    systick_start(TICKS_MS_005);
    // doing 250 ms will overload timer so need to do 5ms 50 times
    int counter_to_250 = 0;

    while (1)
    {
        if (systick_expired()) {
            // increment the counter until reaching 250ms
            counter_to_250++;
            
            if (counter_to_250 == 50) {
                counter_to_250 = 0;

                // read in the value of the push buttons
                reg_val = REG_PUSH_BUTTON_IN;
                if ((reg_val & SW1_MASK) == 0x00) {
                    sw1_pressed = true;
                } else{
                    sw1_pressed = false;
                }

                // if SW1 is pressed, increment the funds and draw the next card
                if (sw1_pressed) {
                    funds += 50;

                    num_of_cards++;
                    hand_index_counter++;

                    if (num_of_cards >= 52) {
                        num_of_cards = 0;
                    }

                    // get hand index with modulo 7
                    hand_index = hand_index_counter % 7;

                    // get suit by dividing the num of cards by number of cards then shift by 2 because of order of suits then modulo 4
                    suit = ((num_of_cards / 13) + 2) % 4;

                    // get card id by doing modulo of 13 then index the value_map
                    value = value_map[num_of_cards % 13];

                    // draw card, may need to clear screen first if hand index is 0

                    card_t next_card = {
                        .border_color = LCD_COLOR_BLUE,
                        .suit = suit,
                        .card_id = value,
                        .hand_index = hand_index
                    };

                    if (hand_index == 0) {
                        lcd_clear_screen(LCD_COLOR_BLACK);

                        screen_display_stats_bet(bet, LCD_COLOR_GREEN);

                        screen_display_stats_player_hand(21, LCD_COLOR_GREEN);

                        screen_display_stats_dealer_hand(19, LCD_COLOR_RED);
                    }

                    screen_display_stats_funds(funds, LCD_COLOR_GREEN);
                    card_draw(&next_card);
                }
            }
            systick_start(TICKS_MS_005);
        }
        

    }
}

#endif