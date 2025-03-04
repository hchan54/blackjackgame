/**
 * @file deck.c
 * @author Jake Yun and Hunter Chan
 * @brief 
 * @version 0.1
 * @date 2025-01-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "deck.h"
 #include "cyip_pass.h"

 extern cyhal_trng_t trng_obj;
 
 // array of const for the card values
 const card_id_t value_map[] = {CARD_ID_2, CARD_ID_3, CARD_ID_4, CARD_ID_5,
    CARD_ID_6, CARD_ID_7, CARD_ID_8, CARD_ID_9,
    CARD_ID_10, CARD_ID_J, CARD_ID_Q, CARD_ID_K, CARD_ID_A};

/**
 * @brief 
 * Initializes the deck of cards
 * @param deck
 * Pointer to the deck of cards 
 * @return true 
 * @return false 
 */
bool deck_init(deck_t *deck)
{   
    // check valid pointer 
    if (deck == NULL) 
    {   
        return false;
    }

    // index begins at 0
    deck->card_index = 0;

    // initialize entire deck of cards
    while (deck->card_index < 52) 
    {    

        // clovers -> spades -> hearts -> diamonds  
        deck->cards[deck->card_index].suit = ((deck->card_index / 13) + 2) % 4;
        
        // assign the card value against value map 
        deck->cards[deck->card_index].card_id = value_map[deck->card_index % 13];
        deck->cards[deck->card_index].border_color = LCD_COLOR_BLUE;        
        deck->cards[deck->card_index].hand_index = deck->card_index % 7;
        deck->card_index++;
    }

    return true;
}   

/**
 * @brief 
 * Function used to randomize the card deck
 * @param arr 
 */
void deck_randomize(deck_t *deck) 
{ 
    
    u_int8_t random_number;

    // Fisher-Yates shuffle algorithm
    // iterate backwards through the deck
    for (int i = deck->card_index; i >= 0; i--)
    {
        // generate a random number in range of 0-51
        random_number = cyhal_trng_generate(&trng_obj) % 52;
        // swap card with random card
        card_t temp = deck->cards[i];
        deck->cards[i] = deck->cards[random_number];
        deck->cards[random_number] = temp;
    }
}