/**
 * @file hw01.c
 * @author Hunter Chan and Jake Yun
 * @brief
 * @version 0.1
 * @date 2025-01-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "hw03.h"
#include "io-lcd.h"
#include "io-leds.h"
#include "joystick.h"
#include "light-sensor.h"
#include "score.h"
#include "screen.h"
#include "timer_050_ms.h"
#include <stdio.h>

#if defined(HW03)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW03";
char STUDENTS[] = "Hunter Chan and Jake Yun";

/* Random Number Generator Handle*/
cyhal_trng_t trng_obj;

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void) {
  /* Enable the push buttons*/
  push_buttons_init(false);

  console_init();

  joystick_init();

  ece353_enable_lcd();

  i2c_init();
  
  // Set bit 7 as input, bits 6-0 as outputs
  io_expander_set_configuration(0x80);  
  
  // Turn OFF all LEDs
  io_expander_set_output_port(0x00); 
 
  // Turn on io expander interrupts
  io_expander_enable_int();          
  
  spi_init();
  eeprom_cs_init();

  timer_050_ms_start();
  timer_250_ms_start();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 */
void main_app(void) {

  printf("\x1b[2J\x1b[;H");
  printf("**************************************************\n\r");
  printf("* %s\n\r", APP_DESCRIPTION);
  printf("* Date: %s\n\r", __DATE__);
  printf("* Time: %s\n\r", __TIME__);
  printf("* Name:%s\n\r", NAME);
  printf("**************************************************\n\r");

  ltr_light_sensor_start();
  
  // local variable initialization 
  uint16_t funds = 0; // player funds
  uint16_t bet = 0; // player bet
  uint16_t prev_funds = 0;
  uint16_t prev_bet = 0; // previous bet

  int LED_count = 0; // number of LEDs on
   
  uint16_t fcolor = LCD_COLOR_GREEN; // current LCD color
  uint16_t prev_fcolor = LCD_COLOR_GREEN; // previous LCD color
  uint16_t ch0_data = 0; // channel 0 data

  screen_display_stats_funds(funds, fcolor); // update the funds on the LCD
  screen_display_stats_bet(bet, fcolor); // update the bet on the LCD

  while (1) 
  {
    
    // check if the joystick is pressed
    if (ECE353_Events.joystick) 
    {
      // increase the bet by 50 if the joystick is up
      if (joystick_get_pos() == JOYSTICK_POS_UP)
      {
        bet += 50;
      }
      else if (joystick_get_pos() == JOYSTICK_POS_DOWN) // decrease the bet by 50 if the joystick is down
      {
        if (bet >= 50) // cannot have a negative bet
        {
          bet -= 50;
        }
      }

      ECE353_Events.joystick = 0; // reset the joystick event
    }
    
    // sw2 for turning on io expander LEDs
    if (ECE353_Events.sw2) { 
      
      LED_count++; // increment LED count
      
      if (LED_count > 7) { // if all LEDs are on, turn them off
        LED_count = 0;
      }

      // active high LEDs so we mask bits with LED_count
      uint8_t led_mask = (1 << LED_count) - 1;
      
      // set the output port to the led mask
      io_expander_set_output_port(led_mask);

      ECE353_Events.sw2 = 0; // reset the event flag
    }

    // 250ms for light sensor 
    if (ECE353_Events.timer_250_ms) 
    {
      ch0_data = ltr_light_sensor_get_ch0(); // get the channel 0 data
      
      if (ch0_data < 100) // set LCD color blue 
      {
        fcolor = LCD_COLOR_BLUE;
      }
      else if (ch0_data > 500) // set LCD color red 
      {
        fcolor = LCD_COLOR_RED;
      }
      else // default to green
      {
        fcolor = LCD_COLOR_GREEN;
      }
      
      ECE353_Events.timer_250_ms = 0; // reset the timer event
    }

    // reset the bet and funds if io expander interrupt is triggered
    if (ECE353_Events.io_expander) {
      bet = 0;
      funds = 0;
      
      // reset value of funds in eeprom
      score_write(funds);

      ECE353_Events.io_expander = 0; // reset event
    }

    funds = score_read(); // read the funds from the EEPROM

    // write to EEPROM if the bet is greater than or equal to the funds
    if (bet > funds)
    {
        funds = bet; // set the funds to the bet if the bet is greater or equal to the funds
        score_write(funds); // write the funds to the EEPROM
    }

    if (fcolor != prev_fcolor || prev_bet != bet || prev_funds != funds) // check if the color has changed
    {
      screen_display_stats_funds(funds, fcolor); // update the funds on the LCD
      screen_display_stats_bet(bet, fcolor); // update the bet on the LCD
      prev_fcolor = fcolor; // update the previous color
      prev_bet = bet; // update the previous bet
      prev_funds = funds; // update the previous funds
    }
  }
}
#endif