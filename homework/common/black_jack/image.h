/**
 * @file image.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #ifndef __IMAGE_H__
 #define __IMAGE_H__

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    IMAGE_TYPE_HEART = 0,           /* Image used to render cards with a suit that is a heart*/
    IMAGE_TYPE_DIAMOND = 1,         /* Image used to render cards with a suit that is a diamond*/
    IMAGE_TYPE_CLUB = 2,            /* Image used to render cards with a suit that is a club*/
    IMAGE_TYPE_SPADE = 3,           /* Image used to render cards with a suit that is a spade*/
    IMAGE_TYPE_START_SCREEN = 4,    /* Image used to display the start screen */
    IMAGE_TYPE_BET_SCREEN = 5,      /* Image used to display the bet screen */
    IMAGE_TYPE_FONT = 6,            /* Image is an ASCII character */
} image_type_t;

typedef struct 
{
    image_type_t    image_type;     /* Used to identify the image type*/
    uint8_t         *bitmap;        /* Address of the bitmap for the current image*/
    uint16_t        width;          /* Width in pixels */
    uint16_t        height;         /* Height in pixels */
    uint16_t        fcolor;         /* image foreground color */
    uint16_t        bcolor;         /* image background color */
} image_t;

 bool image_get_info(image_type_t img_type, image_t *image);

 #endif