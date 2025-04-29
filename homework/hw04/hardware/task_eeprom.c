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
#include "hw04.h"

#if defined(HW04) 

/* Event Groups */
extern EventGroupHandle_t eg_UI;

//QueueHandle_t q_EEPROM;

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
    eeprom_msg_t msg;
    u_int16_t score;

    for (;;)
    {
        // wait for message to arrive in queue
        if (xQueueReceive(q_EEPROM, &msg, portMAX_DELAY) == pdTRUE)
        {
            // check the command of the message
            switch (msg.operation)
            {
                case EEPROM_READ:
                    // read then return value
                    score = score_read();
                    xQueueSend(msg.return_queue, &score, portMAX_DELAY);
                    break;

                case EEPROM_WRITE:
                    // write the score to the EEPROM
                    score_write(msg.score);
                    break;

                default:
                    break;
            }
        }

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
