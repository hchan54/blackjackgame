/**
 * @file hw01.c
 * @author <ADD YOUR NAMES>
 * @brief 
 * @version 0.1
 * @date 2025-01-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #include "hw02.h"


#if defined(HW02)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW02";
char STUDENTS[] = "Your Names";

/* Random Number Generator Handle*/
cyhal_trng_t trng_obj;

/* Allocate space for two decks of cards */
deck_t *DeckA;
deck_t *DeckB;


/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE.
 *
 * This function is implemented in the iceXX.c file for the ICE you are
 * working on.
 */
void peripheral_init(void)
{
    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);

    /* Enable the push buttons*/
    push_buttons_init(false);

    ece353_enable_lcd();

    joystick_init();

    console_init();

    timer_050_ms_start();
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 */
void main_app(void)
{

    printf("\x1b[2J\x1b[;H");
    printf("**************************************************\n\r");
    printf("* %s\n\r", APP_DESCRIPTION);
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Name:%s\n\r", NAME);
    printf("**************************************************\n\r");

    while (1)
    {

    }
}

#endif