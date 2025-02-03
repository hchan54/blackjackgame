 #ifndef __BLACK_JACK_H__
 #define __BLACK_JACK_H__

#undef HW_ENABLE_FREERTOS

/*****************************************************************************
*  Homework Common Includes
*****************************************************************************/
#include "main.h"
#include "homework/common/black_jack/black_jack_images.h"
#include "homework/common/black_jack/card.h"
//#include "homework/common/black_jack/hand.h"
//#include "homework/common/black_jack/deck.h"
#include "homework/common/black_jack/fonts.h"
#include "homework/common/black_jack/image.h"
#include "homework/common/black_jack/screen.h"
//#include "homework/common/black_jack/game_info.h"

/*****************************************************************************
*  Homework FreeRTOS Includes
*****************************************************************************/
#ifdef HW_ENABLE_FREERTOS
/* Will add headers in future homework */
#endif

/*****************************************************************************
* Software Events 
*****************************************************************************/
#define EVENT_UI_SW1                (1 << 0)
#define EVENT_UI_SW2                (1 << 1)
#define EVENT_UI_SW3                (1 << 2)
#define EVENT_UI_JOY_UP             (1 << 3)
#define EVENT_UI_JOY_DOWN           (1 << 4)


/******************************************************************************
 * Task Priorities
 *****************************************************************************/
#ifdef HW_ENABLE_FREERTOS
#define ECE353_TASK_PRIORITY_BOTTOM_HALF  6
#define ECE353_TASK_PRIORITY_UI_INPUT     5
#define ECE353_TASK_PRIORITY_UI_OUTPUT    4
#define ECE353_TASK_PRIORITY_FSM          3
#endif

/*****************************************************************************
*  Homework Global Variables
*****************************************************************************/
//extern game_info_t      Game_Info;
extern cyhal_trng_t     trng_obj;

#ifdef HW_ENABLE_FREERTOS
/* Event Groups */
extern EventGroupHandle_t eg_UI;
extern SemaphoreHandle_t sem_Game_Info;
#endif

#endif