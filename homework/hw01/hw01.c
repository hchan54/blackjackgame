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
 #include "hw01.h"
#include "card.h"
#include "console.h"
#include "cyhal_system.h"
#include "image.h"
#include "io-lcd.h"
#include "screen.h"

#if defined(HW01)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353: S25 HW01";
char STUDENTS[] = "ADD YOUR NAMES";     /* Modify */
char TEAM[] = "TeamXX";                 /* Modify */

 cyhal_trng_t trng_obj;


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

    console_init();
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
    printf("* Team:%s\n\r", TEAM);
    printf("* Names:%s\n\r", STUDENTS);
    printf("**************************************************\n\r");

    while (1)
    {
        /* Modify */
    }
}

#endif