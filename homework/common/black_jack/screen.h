/**
 * @file screen.h
 * @author your name (you@domain.com)
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

/******************************************************************************
 *  Macros
 *****************************************************************************/

#define LOC_TEXT_ROW_1_Y                 3
#define LOC_TEXT_ROW_2_Y                 43 

#define LOC_TEXT_COL_1_X                 5
#define LOC_TEXT_COL_2_X                 120 
#define LOC_TEXT_COL_3_X                 260 

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
    SCREEN_CMD_DRAW_BET_SCREEN,
    SCREEN_CMD_DRAW_HAND_STATUS,
} screen_cmd_t;

/******************************************************************************
 * Function Declarations                                                      *
 *****************************************************************************/
void screen_display_stats_funds(int16_t funds, uint16_t fcolor);
void screen_display_stats_bet(int16_t bet, uint16_t fcolor);
void screen_display_stats_dealer_hand(int16_t hand_value, uint16_t fcolor);
void screen_display_stats_player_hand(int16_t hand_value, uint16_t fcolor);
void screen_display_string( char *s, uint16_t loc_x, uint16_t loc_y, uint16_t fcolor, uint16_t bcolor) ;
#endif