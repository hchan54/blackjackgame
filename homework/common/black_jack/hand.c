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
 * @brief Get the blackjack value object, helper function
 * 
 * @param card 
 * @return int value of the card as an int
 */
static int get_blackjack_value(card_id_t card) {
    switch (card) {
        case CARD_ID_2: return 2;
        case CARD_ID_3: return 3;
        case CARD_ID_4: return 4;
        case CARD_ID_5: return 5;
        case CARD_ID_6: return 6;
        case CARD_ID_7: return 7;
        case CARD_ID_8: return 8;
        case CARD_ID_9: return 9;
        case CARD_ID_10:
        case CARD_ID_J:
        case CARD_ID_Q:
        case CARD_ID_K:
            return 10;
        case CARD_ID_A:
            return 11; // Could return 1 or 11 depending on game state
        default:
            return 0; // Invalid card
    }
}

/**
 * @brief 
 * Calculates the value of a players hand.
 * @return 
 */
static void hand_calc_value(hand_t *hand)
{
    u_int16_t total = 0;
    u_int16_t num_aces = 0;
    // iterate through each card in hand
    for (int i = 0; i < hand->num_cards; i++)
    {
        // check for ace
        if (hand->cards[i].card_id == CARD_ID_A)
        {
            num_aces++;
        }
        else
        {
            // otherwise call helper method
            total += get_blackjack_value(hand->cards[i].card_id);
        }
    }

    // consider value of all the aces
    for (int i = 0; i < num_aces; i++)
    {
        // check if 11 would overflow
        if (total + 11 > 21)
        {
            total += 1; // Add 1 instead of 11
        }
        else
        {
            total += 11; // Add 11
        }
    }
    hand->total = total;
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
    // check for null argument
    if( hand == NULL || card == NULL)
    {
        return false;
    }
    
    // update card index
    card->hand_index = hand->num_cards;

    // copy card to hand
    hand->cards[hand->num_cards] = *card;
    hand->num_cards++;

    // get new value of hand
    hand_calc_value(hand);

    return true;
}
