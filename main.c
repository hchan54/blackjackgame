/**
 * @file main.c
 * @author Joe Krachey (joe.krachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "main.h"

volatile ece353_events_t ECE353_Events;
char NAME[] = "Hunter Chan";

int main(void)
{
    cy_rslt_t rslt;

    rslt = cybsp_init() ;   
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    __enable_irq();

    peripheral_init(); //define peripherals of the board
    main_app(); //define behavior of executable 

    for (;;)
    {
    }
    
}

/* [] END OF FILE */