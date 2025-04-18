/**
 * @file card.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #ifndef __CARD_H__
 #define __CARD_H__

#include <stdint.h>
#include "drivers/io-lcd.h"
#include "black_jack_images.h"
#include "fonts.h"
#include "image.h"

#define CARD_Y_OUTER_HEIGHT 150
#define CARD_X_OUTER_WIDTH  100

#define CARD_Y_INNER_HEIGHT 142
#define CARD_X_INNER_WIDTH  92

#define CARD_HL_Y_UPPER     (109) 
#define CARD_HL_Y_CENTER    (160)
#define CARD_HL_Y_LOWER     (211) 

#define CARD_VL_X_TEXT_DELTA    (35)
#define CARD_VL_X_CARD_DELTA    (35)

#define CARD_VL_X0_CENTER       (54)
#define CARD_VL_X1_CENTER       (CARD_VL_X0_CENTER + CARD_VL_X_CARD_DELTA)
#define CARD_VL_X2_CENTER       (CARD_VL_X1_CENTER + CARD_VL_X_CARD_DELTA)
#define CARD_VL_X3_CENTER       (CARD_VL_X2_CENTER + CARD_VL_X_CARD_DELTA)
#define CARD_VL_X4_CENTER       (CARD_VL_X3_CENTER + CARD_VL_X_CARD_DELTA)
#define CARD_VL_X5_CENTER       (CARD_VL_X4_CENTER + CARD_VL_X_CARD_DELTA)
#define CARD_VL_X6_CENTER       (CARD_VL_X5_CENTER + CARD_VL_X_CARD_DELTA)
#define CARD_VL_X7_CENTER       (CARD_VL_X6_CENTER + CARD_VL_X_CARD_DELTA)

typedef enum 
{
    CARD_ID_2 = '2',
    CARD_ID_3 = '3',
    CARD_ID_4 = '4',
    CARD_ID_5 = '5',
    CARD_ID_6 = '6',
    CARD_ID_7 = '7',
    CARD_ID_8 = '8',
    CARD_ID_9 = '9',
    CARD_ID_10 = 'T',
    CARD_ID_J = 'J',
    CARD_ID_Q = 'Q',
    CARD_ID_K = 'K',
    CARD_ID_A = 'A',
} card_id_t;

typedef struct
{
    uint16_t coord_x;
    uint16_t coord_y;
} coordinate_t;

typedef struct 
{
   image_type_t suit;           /* Defines what suit the card is*/
   card_id_t    card_id;        /* Used to identify the value of the card */
   bool         hidden;         /* Should the value and suit be displayed or is it hidden */
   uint16_t     card_bcolor;    /* Added to HW03 to allow light sensor to determine card color*/
   uint16_t     border_color;   /* The color of the cards border */
   uint16_t     hand_index;     /* Used to identify where a card should be drawn*/
} card_t;

/**
 * @brief 
 *  Draws the specified card 
 * @param card 
 */
bool card_draw(card_t *card);

 #endif