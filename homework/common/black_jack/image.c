/**
 * @file image.c
 * @author Hunter Chan and Jake Yun
 * @brief 
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #include "image.h"
 #include "black_jack_images.h"

/**
 * @brief 
 * Initializes image_t pointer based on the card suit provided  in img_type.
 *
 *  Set the width of the image based on the image_type_t passed in
 *  Set the height of the image based on the image_type_t passed in
 *  Set the fcolor to red if the image type is a HEART or DIAMOND 
 *  Set the fcolor to black if the image type is a CLUB or SPADE
 *  Set the fcolor to blue if the image type is BET_SCREEN OR START_SCREEN 
 *  Set the bcolor to white for images associated with cards. 
 *  Set the bcolor to black for images associated with splash screens. 
 * @param img_type
 * The type of image is used to identify which image is being requested 
 * @param image 
 * Pointer to the image information
 * @return true
 * A valid Image was found 
 * @return false 
 * No Image found
 */
 bool image_get_info(image_type_t img_type, image_t *image)
 {
   
   //initialize the image pointer based on the image type
   switch(img_type) 
   {
      case IMAGE_TYPE_HEART:
         image->width = IMAGE_PIXELS_WIDTH_HEART;
         image->height = IMAGE_PIXELS_HEIGHT_HEART;
         image->fcolor = LCD_COLOR_RED;
         image->bcolor = LCD_COLOR_WHITE;
         image->bitmap = IMAGE_BITMAP_HEART;
         image->image_type = IMAGE_TYPE_HEART;
         break;
      case IMAGE_TYPE_DIAMOND:
         image->width = IMAGE_PIXELS_WIDTH_DIAMOND;
         image->height = IMAGE_PIXELS_HEIGHT_DIAMOND;
         image->fcolor = LCD_COLOR_RED;
         image->bcolor = LCD_COLOR_WHITE;
         image->bitmap = IMAGE_BITMAP_DIAMOND;
         image->image_type = IMAGE_TYPE_DIAMOND;
         break;
      case IMAGE_TYPE_CLUB:
         image->width = IMAGE_PIXELS_WIDTH_CLUB;
         image->height = IMAGE_PIXELS_HEIGHT_CLUB;
         image->fcolor = LCD_COLOR_BLACK;
         image->bcolor = LCD_COLOR_WHITE;
         image->bitmap = IMAGE_BITMAP_CLUB;
         image->image_type = IMAGE_TYPE_CLUB;
         break;
      case IMAGE_TYPE_SPADE:
         image->width = IMAGE_PIXELS_WIDTH_SPADE;
         image->height = IMAGE_PIXELS_HEIGHT_SPADE;
         image->fcolor = LCD_COLOR_BLACK;
         image->bcolor = LCD_COLOR_WHITE;
         image->bitmap = IMAGE_BITMAP_SPADE;
         image->image_type = IMAGE_TYPE_SPADE;
         break;
      case IMAGE_TYPE_START_SCREEN:
         image->image_type = IMAGE_TYPE_START_SCREEN;
         image->width = IMAGE_PIXELS_WIDTH_START_SCREEN;
         image->height = IMAGE_PIXELS_HEIGHT_START_SCREEN;
         image->fcolor = LCD_COLOR_RED;
         image->bcolor = LCD_COLOR_BLACK;
         image->bitmap = IMAGE_BITMAP_START_SCREEN;
         break;
      case IMAGE_TYPE_BET_SCREEN:
         image->image_type = IMAGE_TYPE_BET_SCREEN;
         image->width = IMAGE_PIXELS_WIDTH_BET_SCREEN;
         image->height = IMAGE_PIXELS_HEIGHT_BET_SCREEN;
         image->fcolor = LCD_COLOR_BLUE;
         image->bcolor = LCD_COLOR_BLACK;
         image->bitmap = IMAGE_BITMAP_BET_SCREEN;
         break;
      default:
         return false;
   }

   return true;
 }