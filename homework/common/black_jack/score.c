/**
 * @file score.c
 * @author Hunter Chan and Jake Yun
 * @brief 
 * @version 0.1
 * @date 2025-02-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
 #include "score.h"
#include "eeprom.h"

/**
 * @brief 
 *  Writes a 16-bit unsigned number to the eeprom
 *  Data is written to addresses 0x10 and 0x11
 * @param score 
 */
void score_write(uint16_t score)
{   
    eeprom_wait_for_write(); // wait for any outstanding writes to complete

    eeprom_write_enable(); // enable writes to EEPROM
    
    // write high byte to address 0x10 and low byte to 0x11
    eeprom_write_byte(0x10, (score >> 8) & 0xFF);
    eeprom_write_byte(0x11, score & 0xFF);
}

/**
 * @brief 
 * Reads the current high water mark for the funds from the EEPROM
 * @return uint16_t
 * The value of the high water mark for the funds  
 */
uint16_t score_read(void)
{
    uint16_t score_mark = 0;

    // read high byte from address 0x10 and low byte from 0x11
    score_mark |= (eeprom_read_byte(0x10) << 8); // read high byte
    score_mark |= eeprom_read_byte(0x11); // read low byte

    return score_mark; // return the score
}