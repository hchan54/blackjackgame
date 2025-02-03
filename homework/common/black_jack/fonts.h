/**
 * @file fonts.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #ifndef __FONTS_H__
 #define __FONTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "image.h"
#include "drivers/io-lcd.h"

typedef struct
{
    uint16_t width;     /* Character Width */
    uint16_t height;    /* Character Height*/
    uint16_t offset;    /* Offset of Character in the font BITMAP array */
} FONT_CHAR_INFO;

bool font_get_image(char c, image_t *image);


 #endif