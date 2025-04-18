/**
 * @file game_info.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __GAME_INFO_H__
#define __GAME_INFO_H__

#include <stdint.h>
#include "card.h"
#include "hand.h"
#include "deck.h"

typedef struct 
{
    /* Stores the players current funds */
    int32_t     player_funds;       
    /* Stores the bet value for the current hand*/
    int32_t     player_bet;    
    /* Pointer to the deck of cards */
    deck_t      *deck;              
    /* Pointer to the dealer's hand (collection of up to 11 cards) */
    hand_t      *dealer_hand;       
   /* Pointer to the player's hand (collection of up to 11 cards )*/
    hand_t      *player_hand;       
} game_info_t;

#endif