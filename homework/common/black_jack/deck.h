/**
 * @file deck.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #ifndef __DECK_H__
 #define __DECK_H__

 #include "card.h"

typedef struct
{
    card_t cards[52];
    int16_t card_index;
} deck_t;

/**
 * @brief 
 * Initializes the deck of cards
 * @param deck
 * Pointer to the deck of cards 
 * @return true 
 * @return false 
 */
bool deck_init(deck_t *deck);

/**
 * @brief 
 * Function used to randomize the card deck
 * @param arr 
 */
void deck_randomize(deck_t *deck);

/**
 * @brief 
 * Get the next card from the deck
 * @param deck 
 * @return card_t* 
 */
card_t * deck_draw_card(deck_t *deck);


 #endif
