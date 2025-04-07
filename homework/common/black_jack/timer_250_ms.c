/**
 * @file pyl_handler_tmr_050_ms.c
 * @author Hunter Chan and Jake Yun
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "timer_250_ms.h"
#include "ece353_events.h"
#include "screen.h"

#if defined (HW03) 

 /* 250ms timer handles */
cyhal_timer_t Timer_MS_250_Obj; 
cyhal_timer_cfg_t Timer_MS_250_Cfg;

 /**
  * @brief 
  * Handler for the 250mS Timer Interrupt
  */
 void timer_250_ms_handler(void *callback_arg, cyhal_timer_event_t event)
 {
    ECE353_Events.timer_250_ms = 1; // set the event flag for the 250ms timer
 }

 
 /**
  * @brief 
  * Add the code required to initialize a 250mS TCPWM based timer interrupt
  */
void timer_250_ms_start(void)
{
  // set the timer configuration
  timer_init(&Timer_MS_250_Obj, &Timer_MS_250_Cfg, TICKS_MS_005 * 50, timer_250_ms_handler);
  
  // start the timer
  cyhal_timer_start(&Timer_MS_250_Obj);
}

#endif
