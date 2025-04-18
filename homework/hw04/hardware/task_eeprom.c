/**
 * @file task_io_expander.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "task_eeprom.h"

#if defined(HW04) 

/* Event Groups */
extern EventGroupHandle_t eg_UI;

QueueHandle_t q_EEPROM;

/**
 * @brief 
 * Game Keeper task for the EEPROM
 * @param param 
 * Not Used
 */
void task_eeprom(void *param)
{
    /* Suppress warning for unused parameter */
    (void)param;

    /* Repeatedly running part of the task */
    for (;;)
    {
        /* ADD CODE */
    }
}

void task_eeprom_init(void)
{
    /* Enable the SPI interface */
    spi_init();

    /* Configure the IO pin used to control the chip select*/
    eeprom_cs_init();

    q_EEPROM = xQueueCreate(1, sizeof(eeprom_msg_t));

    xTaskCreate(
        task_eeprom,
        "Task EEPROM",
        configMINIMAL_STACK_SIZE,
        NULL,
        ECE353_TASK_PRIORITY_UI_INPUT,
        NULL);
}

#endif
