/**
 * @file hw04.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __HW04_H__
#define __HW04_H__

#include "main.h"

#if defined(HW04)

#include "black_jack.h"
#include "black_jack_images.h"
#include "card.h"
#include "deck.h"
#include "fonts.h"
#include "game_info.h"
#include "hand.h"
#include "image.h"
#include "score.h"
#include "screen.h"

#include "task_console.h"
#include "task_eeprom.h"
#include "task_io_expander.h"
#include "task_joystick.h"
#include "task_screen.h"
#include "task_sw.h"

/* ADD CODE */
/* When you are ready to test a gate keeper task, change #undef to #define */
#undef   HW04_ENABLE_TASK_SW
#undef   HW04_ENABLE_TASK_JOYSTICK
#undef   HW04_ENABLE_TASK_EEPROM
#undef   HW04_ENABLE_TASK_IO_EXPANDER
#undef   HW04_ENABLE_TASK_LCD

/* ADD CODE */
/* When you are ready to test your FSM, change the following #define to #undef */
#define HW04_ENABLE_TASK_TEST

/* FSM Task Handles */
extern TaskHandle_t Task_Handle_FSM_BET;
extern TaskHandle_t Task_Handle_FSM_DEALER_HIT;
extern TaskHandle_t Task_Handle_FSM_DEALER_SHOW;
extern TaskHandle_t Task_Handle_FSM_HAND_COMPLETE;
extern TaskHandle_t Task_Handle_FSM_HIT;
extern TaskHandle_t Task_Handle_FSM_SHUFFLE;
extern TaskHandle_t Task_Handle_FSM_START;
extern TaskHandle_t Task_Handle_FSM_TEST;

/* FSM tasks and initialization functions */
void task_fsm_bet(void *param);
void task_fsm_bet_init(void);
void task_fsm_dealer_hit(void *param);
void task_fsm_dealer_hit_init(void);
void task_fsm_dealer_show(void *param);
void task_fsm_dealer_show_init(void);
void task_fsm_hand_complete(void *param);
void task_fsm_hand_complete_init(void);
void task_fsm_hit(void *param);
void task_fsm_hit_init(void);
void task_fsm_shuffle(void *param);
void task_fsm_shuffle_init(void);
void task_fsm_start(void *param);
void task_fsm_start_init(void);
void task_fsm_test(void *param);
void task_fsm_test_init(void);

#endif
#endif
