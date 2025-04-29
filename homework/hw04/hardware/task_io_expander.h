#ifndef __TASK_IO_EXPANDER_H__
#define __TASK_IO_EXPANDER_H__

#include "main.h"

#if defined(HW04)

#include "black_jack.h"

extern QueueHandle_t q_IO_Exp;

void task_io_expander_init(void);
void task_io_expander(void *param);
void hw04_handler_io_exp(void *callback_arg, cyhal_gpio_event_t event);

#endif

#endif
