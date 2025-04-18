/**
 * @file hand.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #ifndef __HAND_H__
 #define __HAND_H__

#include "card.h"

typedef struct
{
    card_t  cards[11];      /* Max number of cards a black jack hand can have is 11*/
    uint8_t num_cards;      /* Current number of cards in the hand */
    int16_t total;          /* The total value of the hand */
} hand_t;


bool hand_init(hand_t *hand);
bool hand_add_card(hand_t *hand, card_t *card);
card_t * hand_get_last_card(hand_t *hand);


 #endif