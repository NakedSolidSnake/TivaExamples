/*
 * timers.h
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_DRIVERS_TIMERS_H_
#define DEVICE_DRIVERS_DRIVERS_TIMERS_H_

#include <stdint.h>

void Timer0_init_low_level(void);
void Timer0_ClearInterrupt(void);
void Timer0_set_value(uint32_t period);

#endif /* DEVICE_DRIVERS_DRIVERS_TIMERS_H_ */
