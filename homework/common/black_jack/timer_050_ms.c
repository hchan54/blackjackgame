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

/* The requirements for the handler are:
Detect when SW1, SW2, or SW3 are pressed by setting the  appropriate fields in ECE353_Events
Pressing a button should only result in a single detection, regardless of the length of the button press.
Detect when the joystick is moved out of the center position by setting the  appropriate fields in ECE353_Events
Store the current location of the joystick in a global variable that can be accessed by the main application code.
*/

 void handler_timer_050_ms(void *callback_arg, cyhal_timer_event_t event)
 {
    // variables to store button states
    static bool sw1, sw2, sw3;
    static bool sw1_prev, sw2_prev, sw3_prev;
    static joystick_position_t curr_position = JOYSTICK_POS_CENTER;
    static joystick_position_t prev_position = JOYSTICK_POS_CENTER;

    uint32_t reg_val = PORT_BUTTONS->IN;

    // check if button 1 is pressed
    if ((reg_val & SW1_MASK) == 0x00) {
        sw1 = true;
        // check for an edge by comparing with prev
        if (sw1 != sw1_prev) {
            ECE353_Events.sw1 = 1;
        }
    } else {
        sw1 = false;
    }

    // same logic for buttons 2 and 3
    if ((reg_val & SW2_MASK) == 0x00) {
        sw2 = true;
        if (sw2 != sw2_prev) {
            ECE353_Events.sw2 = 1;
        }
    } else {
        sw2 = false;
    }

    if ((reg_val & SW3_MASK) == 0x00) {
        sw3 = true;
        if (sw3 != sw3_prev) {
            ECE353_Events.sw3 = 1;
        }
    } else {
        sw3 = false;
    }

    // read joystick position
    prev_position = curr_position;
    curr_position = joystick_get_pos();
    // check if joystick moved FROM center
    if (curr_position != prev_position && curr_position != JOYSTICK_POS_CENTER) {
        ECE353_Events.joystick = 1;
    }

    // set previous values for next loop
    sw1_prev = sw1;
    sw2_prev = sw2;
    sw3_prev = sw3;

 }

/* Configure a general purpose timer to generate an interrupt every 50mS*/
 void timer_050_ms_start(void)
 {
    // initialize and start timer
    timer_init(&Timer_MS_050_Obj, &Timer_MS_050_Cfg, TICKS_MS_005 * 10, handler_timer_050_ms);
    
    cyhal_timer_start(&Timer_MS_050_Obj);
 }

#endif
