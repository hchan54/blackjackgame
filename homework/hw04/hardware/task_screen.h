/**
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __TASK_SCREEN_H__
#define __TASK_SCREEN_H__

#include "black_jack.h"

#if defined(HW04)

#define LOC_HAND_STATUS_X               (320/2)
#define LOC_HAND_STATUS_Y               (240 - (CARD_X_OUTER_WIDTH/2))

union screen_payload {
   card_t card;
   int16_t funds;
   int16_t bet;
   int16_t hand_value;
   char* str_ptr;
};

typedef struct 
{
    screen_cmd_t cmd;
    union screen_payload payload;
    uint16_t font_color;
} screen_data_t;

extern QueueHandle_t q_Screen;

void task_screen_init(void);
void task_screen(void *param);

#endif

#endif
