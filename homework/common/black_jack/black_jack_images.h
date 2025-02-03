/**
 * @file black_jack_images.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __BLACK_JACK_IMAGES_H__
#define __BLACK_JACK_IMAGES_H__

#include <stdint.h>
#include "image.h"
#include "drivers/io-lcd.h"

#define FONT_PIXELS_HEIGHT  28
#define FONT_PIXELS_WIDTH   16 

#define IMAGE_PIXELS_WIDTH_CLUB         73 
#define IMAGE_PIXELS_HEIGHT_CLUB        67 
#define IMAGE_PIXELS_WIDTH_SPADE        63 
#define IMAGE_PIXELS_HEIGHT_SPADE       77
#define IMAGE_PIXELS_WIDTH_HEART        65 
#define IMAGE_PIXELS_HEIGHT_HEART       68 
#define IMAGE_PIXELS_WIDTH_DIAMOND      61 
#define IMAGE_PIXELS_HEIGHT_DIAMOND     77

// Bitmap sizes for eCE352BlackJack
#define  IMAGE_PIXELS_WIDTH_START_SCREEN  215
#define  IMAGE_PIXELS_HEIGHT_START_SCREEN  225

// Bitmaps for Bet Screen
#define IMAGE_PIXELS_WIDTH_BET_SCREEN  188
#define IMAGE_PIXELS_HEIGHT_BET_SCREEN 69

extern const uint8_t IMAGE_BITMAP_CLUB[];
extern const uint8_t IMAGE_BITMAP_SPADE[];
extern const uint8_t IMAGE_BITMAP_HEART[];
extern const uint8_t IMAGE_BITMAP_DIAMOND[];
extern const uint8_t IMAGE_BITMAP_START_SCREEN[];
extern const uint8_t IMAGE_BITMAP_BET_SCREEN[];


#endif
