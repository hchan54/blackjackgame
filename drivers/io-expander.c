/**
 * @file io-expander.c
 * @author Joe Krachey (jkrachey@wisc.edu)
 * @brief 
 * @version 0.1
 * @date 2023-10-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "io-expander.h"
#include "ece353_events.h"

/** Write a register on the TCA9534
 *
 * @param reg The reg address to read
 * @param value The value to be written
 *
 */
static void io_expander_write_reg(uint8_t reg, uint8_t value)
{
	cy_rslt_t rslt;

	/* ADD CODE */
	/* Allocate the write data packet that will be sent to the IO Expander */
	uint8_t write_data[2] = {reg, value};

	/* ADD CODE */
	/* Use cyhal_i2c_master_write to write the required data to the device. */
	rslt = cyhal_i2c_master_write(&i2c_monarch_obj, TCA9534_SUBORDINATE_ADDR, write_data, 2, 0, true);

	CY_ASSERT(rslt == CY_RSLT_SUCCESS);
}

/** Read a register on the TCA9534
 *
 * @param reg The reg address to read
 *
 */
static uint8_t io_expander_read_reg(uint8_t reg)
{
	cy_rslt_t rslt;
	uint8_t return_val = 0;

	/* ADD CODE */
	/* Allocate the write data packet that will be sent to the IO Expander */
	uint8_t write_data[1] = {reg};
	
	/* ADD CODE */
	/* Allocate the read data packet that will be sent from the IO Expander */
	uint8_t read_data[1];

	/* ADD CODE */
	/* Use cyhal_i2c_master_write to write the required data to the device. */
	rslt = cyhal_i2c_master_write(&i2c_monarch_obj, TCA9534_SUBORDINATE_ADDR, write_data, 1, 0, true);

	CY_ASSERT(rslt == CY_RSLT_SUCCESS);

	/* ADD CODE */
	/* Use cyhal_i2c_master_read to read the required data from the device. */
	rslt = cyhal_i2c_master_read(&i2c_monarch_obj, TCA9534_SUBORDINATE_ADDR, read_data, 1, 0, true);
	
	CY_ASSERT(rslt == CY_RSLT_SUCCESS);

	return return_val;
}

/** Read the value of the input port
 *
 * @param reg The reg address to read
 *
 */
uint8_t io_expander_get_input_port(void)
{
	return io_expander_read_reg(TCA9534_INPUT_PORT_ADDR);

}

/** Write the value of the output port
 *
 * @param value The value written
 *
 */
void io_expander_set_output_port(uint8_t value)
{
	io_expander_write_reg(TCA9534_OUTPUT_PORT_ADDR, value);
}

/** Write the polarity inversion register
 *
 * @param value The value written
 *
 */
void io_expander_set_polarity_inversion(uint8_t value)
{
	io_expander_write_reg(TCA9534_POLARITY_ADDR, value);
}

/** Write the value of the configuration Register
 *
 * @param value The value written
 *
 */
void io_expander_set_configuration(uint8_t value)
{
	io_expander_write_reg(TCA9534_CONFIG_ADDR, value);
}


/** @brief 
 * 
 * This function will handle the IO Expander interrupt
 * 
 */
void handler_io_expander(void *callback_arg, cyhal_gpio_event_t event)
{
	ECE353_Events.io_expander = 1; // set the event flag for the IO Expander interrupt
}

// callback data structure for the IO Expander interrupt
cyhal_gpio_callback_data_t io_expander_cb_data = {
    .callback = io_expander_interrupt_handler,
    .callback_arg = NULL
};

/**
 * @brief 
 * 
 * This function will initialize the IO Expander
 * 
 */
void io_expander_enable_int(void)
{
	/* ADD CODE */
	cy_rslt_t rslt;
	
	/* Initialize the I2C peripheral for the IO Expander */
	rslt = cyhal_gpio_init(PIN_IO_EXPANDER_INT, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, true);
	CY_ASSERT(rslt == CY_RSLT_SUCCESS);

	// register the callback function for the IO Expander interrupt
	cyhal_gpio_register_callback(PIN_IO_EXPANDER_INT, &io_expander_cb_data);
	
	// Enable the interrupt for the IO Expander
	cyhal_gpio_enable_event(PIN_IO_EXPANDER_INT, CYHAL_GPIO_IRQ_FALL, 3, true);
}




