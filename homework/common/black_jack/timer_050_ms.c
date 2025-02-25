/**
 * @file timer_050_ms.c
 * @author ADD YOUR NAMES HERE
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
 #include "timer_050_ms.h"


 #if defined(HW02) || defined (HW03) 
/* 50mS Timer Handles*/
cyhal_timer_t       Timer_MS_050_Obj; 
cyhal_timer_cfg_t   Timer_MS_050_Cfg;

 void handler_timer_050_ms(void *callback_arg, cyhal_timer_event_t event)
 {
 }

/* Configure a general purpose timer to generate an interrupt every 50mS*/
 void timer_050_ms_start(void)
 {
 }

#endif
