/**
 * @file image.c
 * @author <ADD NAME>
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
    return true;
 }