/**
 * @file task_joystick.h
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2025-01-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #ifndef __TASK_JOYSTICK_H__
 #define __TASK_JOYSTICK_H__

 #include "black_jack.h"

#if defined(HW04)

 void task_joystick(void *pvParameters);
void task_joystick_init(void);

#endif

#endif