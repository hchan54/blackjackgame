/**
 * @file timer_050_ms.c
 * @author Jake Yun and Hunter Chan 
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
    // store the states of joystick and switch positions 
    static bool sw1, sw2, sw3;
    static bool sw1_prev, sw2_prev, sw3_prev;
    static joystick_position_t joystick_curr_pos = JOYSTICK_POS_CENTER;
    static joystick_position_t joystick_prev_pos = JOYSTICK_POS_CENTER;

    uint32_t reg_val = PORT_BUTTONS->IN; // read pushbutton values

    // detect SW1 push
    if ((reg_val & SW1_MASK) == 0x00) 
    {
        sw1 = true; 
        // edge detection 
        if (sw1 != sw1_prev) 
        {
            ECE353_Events.sw1 = 1;
        }
    }
    else 
    {
        sw1 = false; 
    }

    // detect SW2 push
    if ((reg_val & SW2_MASK) == 0x00) 
    {
        sw2 = true; 
        // edge detection
        if (sw2 != sw2_prev) 
        {
            ECE353_Events.sw2 = 1;
        }
    }
    else 
    {
        sw2 = false; 
    }

    // detect SW3 push
    if ((reg_val & SW3_MASK) == 0x00)
    {
        sw3 = true; 
        // edge detection
        if (sw3 != sw3_prev) 
        {
            ECE353_Events.sw3 = 1;
        }
    }
    else 
    {
        sw1 = false; 
    }

    // store the previous joystick position for reference 
    joystick_prev_pos = joystick_curr_pos;
    joystick_curr_pos = joystick_get_pos(); 
    
    // joystick has moved since center 
    if (joystick_curr_pos != JOYSTICK_POS_CENTER && joystick_curr_pos != joystick_prev_pos) 
    {
        ECE353_Events.joystick = 1;
    }

    // store previous switch states for edge detection 
    sw1_prev = sw1;
    sw2_prev = sw2;
    sw3_prev = sw3;
}

/* Configure a general purpose timer to generate an interrupt every 50mS*/
 void timer_050_ms_start(void)
 {
    // initialize and start 50ms timer 
    timer_init(&Timer_MS_050_Obj, &Timer_MS_050_Cfg, TICKS_MS_005 * 10, handler_timer_050_ms);
    cyhal_timer_start(&Timer_MS_050_Obj);
 }

#endif
