/**
 * @file hand.c
 * @author
 * @brief 
 * @version 0.1
 * @date 2025-01-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "hand.h"
#include "card.h"

 /**
 * @brief 
 * Returns the address of the last card added to the hand
 * @param hand 
 * @return card_t* 
 */
card_t * hand_get_last_card(hand_t *hand)
{
    if( hand == NULL)
    {
        return NULL;
    }
    else { 
        return &hand->cards[hand->num_cards];
    }
}

/**
 * @brief 
 * Used to initialize a hand. All data fields will be set to 0
 * @param hand 
 * @return true 
 * @return false 
 */
bool hand_init(hand_t *hand)
{
    if(hand != NULL)
    {
        /* While not necessary, we will zero out the memory
           used to store the cards */
        memset(hand->cards, 0, 11*sizeof(card_t));
        hand->num_cards = 0;
        hand->total = 0;
        return true;
    }
    else 
    {
        /* NULL pointer passed in */
        return false;
    }
}

/**
 * @brief 
 * Calculates the value of a players hand.
 * @return 
 */
static void hand_calc_value(hand_t *hand)
{
   hand->total = 0; /* Update the value with the calculated value */ 
}

/**
 * @brief 
 * Adds a card to the player's hand
 * @param hand
 *  Address of the hand data structure 
 * @param card
 *  Address of the card to add to the hand 
 * @return true
 *  card successfully added 
 * @return false
 *  card not added to the hand 
 */
bool hand_add_card(hand_t *hand, card_t *card)
{
    if( hand == NULL || card == NULL)
    {
        return false;
    }
    
    /* Update the hand_index of the card */

    /* Copy the card to the hand */

    /* Increment the number of cards in the hand */

    /* Calculate the new total of the hand */

    return true;
}
