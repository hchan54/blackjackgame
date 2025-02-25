/**
 * @file handler_tmr_050_ms.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #ifndef __TIMER_050_MS_H__
 #define __TIMER_050_MS_H__

#include "main.h"

#if defined(HW02) || defined (HW03) 

extern volatile joystick_position_t Joystick_Pos;

void timer_050_ms_start(void);

 #endif

 #endif