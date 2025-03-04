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
 #include "hw02.h"

#if defined(HW02)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW02";
char STUDENTS[] = "Jake Yun and Hunter Chan";

/* Random Number Generator Handle*/
cyhal_trng_t trng_obj;

/* Allocate space for two decks of cards */
deck_t *DeckA;
deck_t *DeckB;


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

    joystick_init();

    console_init();

    timer_050_ms_start();
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
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");
    
    // initialize decks 
    DeckA = (deck_t*)malloc(sizeof(deck_t)); // control deck
    DeckB = (deck_t*)malloc(sizeof(deck_t)); // random deck 
    
    // check successfull malloc 
    if (DeckA == NULL || DeckB == NULL) 
    {
        printf("decks not allocated correctly");
        exit(1);
    }

    // initialize the decks 
    deck_init(DeckA);
    deck_init(DeckB);

    // set the position of each deck card
    DeckA->cards[0].hand_index = 0;
    DeckB->cards[0].hand_index = 6;

    // draw cards at hand index 
    card_draw(&(DeckA->cards[0]));
    card_draw(&(DeckB->cards[0]));

    // display card stats at 0
    DeckA->card_index = 0;
    DeckB->card_index = 0;

    screen_display_stats_player_hand(DeckA->card_index, LCD_COLOR_GREEN);

    while (1)
    {   
        // sw1 event is active 
        if (ECE353_Events.sw1)
        {
            // randomize the deck 
            deck_randomize(DeckB);

            // set the position of each deck card
            DeckA->cards[0].hand_index = 0;
            DeckB->cards[0].hand_index = 6; 
            
            // display first card of the decks
            card_draw(&(DeckA->cards[0]));
            card_draw(&(DeckB->cards[0]));

            // display initial card stats
            DeckA->card_index = 0;
            DeckB->card_index = 0;

            screen_display_stats_player_hand(DeckA->card_index, LCD_COLOR_GREEN);
            
            ECE353_Events.sw1 = 0; // sw1 inactive event  
        }   

        // joystick is moved from center
        if (ECE353_Events.joystick)
        {   
            // new card index with wrapping 
            if (joystick_get_pos() == JOYSTICK_POS_UP) 
            {   
                DeckA->card_index = (DeckA->card_index + 1) % 52;
                DeckB->card_index = (DeckB->card_index + 1) % 52;
            }
            else if (joystick_get_pos() == JOYSTICK_POS_DOWN) 
            {   
                // decrement cards
                DeckA->card_index--;
                DeckB->card_index--;
            
                // Wrap around if the index is less than 0
                if (DeckA->card_index < 0) 
                {
                    DeckA->card_index = DeckB->card_index = 51;
                }
                
                if (DeckB->card_index < 0)
                {
                    DeckB->card_index = DeckB->card_index = 51;
                }

            }
            
            // position cards at the hand index 
            DeckA->cards[DeckA->card_index].hand_index = 0;
            DeckB->cards[DeckB->card_index].hand_index = 6; 

            // draw the current card 
            card_draw(&(DeckA->cards[DeckA->card_index]));
            card_draw(&(DeckB->cards[DeckB->card_index]));

            // display the index of the display card
            screen_display_stats_player_hand(DeckA->card_index, LCD_COLOR_GREEN);

            ECE353_Events.joystick = 0; // joystick inactive event
        }
    }

    // free memory
    free(DeckA);
    free(DeckB);
    
    // dangling pointer 
    DeckA = NULL;
    DeckB = NULL; 
}   


#endif