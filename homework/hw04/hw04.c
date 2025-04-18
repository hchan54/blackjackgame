/**
 * @file hw01a.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2024-01-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "hw04.h"

#if defined(HW04)

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
char APP_DESCRIPTION[] = "ECE353 S25 HW04";
char APP_MEMBERS[] = "Name1, Name2";
char APP_TEAM_NUM[] = "TeamXX";

 cyhal_trng_t trng_obj;

/* Event Groups Shared by all of the states*/
EventGroupHandle_t eg_UI;

SemaphoreHandle_t sem_Game_Info;


game_info_t   Game_Info;

void peripheral_init(void)
{
    /* Initialize the hardware random number generator*/
    cyhal_trng_init(&trng_obj);
}

/**
 * @brief 
 * This function is used to create the tasks for HW04. DO NOT edit this function.
 *
 * If you want to enable/disable a specific task, edit hw04.h to either #define (enable)
 * or #undef (disable) a specific task.
 * 
 */
void tasks_peripheral_init(void)
{

    /* Initialize the Console Task */
    task_console_init();

#ifdef HW04_ENABLE_TASK_SW
    task_sw_init();
#endif

#ifdef HW04_ENABLE_TASK_JOYSTICK
    task_joystick_init();
#endif
    
#ifdef HW04_ENABLE_TASK_EEPROM
    task_eeprom_init();
#endif

#ifdef HW04_ENABLE_TASK_IO_EXPANDER
    task_io_expander_init();
#endif
    
#ifdef HW04_ENABLE_TASK_LCD
    task_screen_init();
#endif

#ifdef HW04_ENABLE_TASK_TEST
   task_fsm_test_init();
#else

    task_fsm_start_init();
   
    task_fsm_shuffle_init();
    
    task_fsm_bet_init();

    task_fsm_dealer_show_init();

    task_fsm_hit_init();

    task_fsm_dealer_hit_init();

    task_fsm_hand_complete_init();
#endif

}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function creates will create the global variables used ot manage the 
 * game data for HW04.  It will also create the tasks and start the FreeRTOS
 * scheduler.
 */
void main_app(void)
{
    /* Initialize the Event Groups*/
    eg_UI = xEventGroupCreate();

    /* Allocate Space for the Deck of Cards */
    Game_Info.deck = pvPortMalloc(sizeof(deck_t));
    
    /* Allocate Space for the Dealer hand */
    Game_Info.dealer_hand = pvPortMalloc(sizeof(hand_t));
    
    /* Allocate Space for the Player hand */
    Game_Info.player_hand = pvPortMalloc(sizeof(hand_t));

    /* Create the Binary semaphore used to grant mutual exclusion 
     * of the Game Data
     */
    sem_Game_Info = xSemaphoreCreateBinary();
    xSemaphoreGive(sem_Game_Info);
    
    tasks_peripheral_init();

    /* Uncomment when ready to test the FSM */
    /* Give a task notification to initialize the FSM */
#ifndef HW04_ENABLE_TASK_TEST
    xTaskNotifyGive(Task_Handle_FSM_START);
#endif

    // Start the scheduler
    vTaskStartScheduler();

    /* RTOS scheduler exited */
    /* Halt the CPU if scheduler exits */
    CY_ASSERT(0);

    for (;;)
    {
    }
}

#endif