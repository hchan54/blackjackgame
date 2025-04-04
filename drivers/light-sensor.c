/**
 * @file light-sensor.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-11-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "light-sensor.h"

uint8_t ltr_reg_read(uint8_t reg);


/**
 * @brief 
 *  Returns the value of the CONTR register
 * @return uint8_t 
 */
uint8_t ltr_light_get_contr(void)
{
    return ltr_reg_read(LTR_REG_CONTR);
}

/**
 * @brief 
 * returns the value of the STATUS register
 * @return uint8_t 
 */
uint8_t ltr_light_sensor_status(void)
{
    return ltr_reg_read(LTR_REG_ALS_STATUS);
}

/**
 * @brief
 * Returns the part ID of the LTR_329ALS-01
 * @return uint8_t
 */
uint8_t ltr_light_sensor_part_id(void)
{
    return ltr_reg_read(LTR_REG_PART_ID);
}

/**
 * @brief 
 *  Returns the manufacturer ID
 * @return uint8_t 
 */
uint8_t ltr_light_sensor_manufac_id(void)
{
    return ltr_reg_read(LTR_REG_MANUFAC_ID);
}



/******************************************************************************
 * COMPLETE THE FUNCTIONS BELOW
******************************************************************************/
/**
 * @brief
 * Returns an 8-bit value based on the provided register address
 * @return uint8_t
 */
uint8_t ltr_reg_read(uint8_t reg)
{
    cy_rslt_t rslt;

    /* ADD CODE */
}
/**
 * @brief 
 * Returns the Channel 0 data reading
 * @return uint16_t 
 */
uint16_t ltr_light_sensor_get_ch0(void)
{
    /* ADD CODE */
}

/**
 * @brief 
 * Returns the Channel 1 data reading
 * @return uint16_t 
 */
uint16_t ltr_light_sensor_get_ch1(void)
{
    /* ADD CODE */
}

/**
 * @brief
 * Set ALS MODE to Active and initiate a software reset
 */
void ltr_light_sensor_start(void)
{
    cy_rslt_t rslt;
    /* ADD CODE */

}