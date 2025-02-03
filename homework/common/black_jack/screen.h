/**
 * @file screen.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2025-01-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "card.h"
#include "image.h"

/******************************************************************************
 *  Macros
 *****************************************************************************/
#define LOC_GAME_LABEL_FUNDS_X          15 
#define LOC_GAME_LABEL_FUNDS_Y          20 

#define LOC_GAME_STATS_FUNDS_X          120
#define LOC_GAME_STATS_FUNDS_Y          20 

#define LOC_GAME_LABEL_BET_X            15
#define LOC_GAME_LABEL_BET_Y            60 

#define LOC_GAME_STATS_BET_X            120 
#define LOC_GAME_STATS_BET_Y            60 

#define LOC_GAME_STATS_PLAYER_HAND_X    260 
#define LOC_GAME_STATS_PLAYER_HAND_Y    20

#define LOC_GAME_STATS_DEALER_HAND_X    260 
#define LOC_GAME_STATS_DEALER_HAND_Y    60 

/* This enumerated type will not be used until a later homework */
#if 0
typedef enum 
{
    SCREEN_CMD_CLEAR_ALL,
    SCREEN_CMD_CLEAR_CARDS,
    SCREEN_CMD_CLEAR_STATS,
    SCREEN_CMD_DRAW_CARD,
    SCREEN_CMD_DRAW_STATS_FUNDS,
    SCREEN_CMD_DRAW_STATS_BET,
    SCREEN_CMD_DRAW_STATS_DEALER_HAND,
    SCREEN_CMD_DRAW_STATS_PLAYER_HAND,
    SCREEN_CMD_DRAW_STATS_ALL,
    SCREEN_CMD_DRAW_SPLASH_SCREEN,
    SCREEN_CMD_DRAW_BET_SCREEN
} screen_cmd_t;
#endif

/******************************************************************************
 * Function Declarations                                                      *
 *****************************************************************************/
void screen_display_stats_funds(int16_t funds, uint16_t fcolor);
void screen_display_stats_bet(int16_t bet, uint16_t fcolor);
void screen_display_stats_dealer_hand(int16_t hand_value, uint16_t fcolor);
void screen_display_stats_player_hand(int16_t hand_value, uint16_t fcolor);

#endif