/*
 * adcs.h
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_DRIVERS_ADCS_H_
#define DEVICE_DRIVERS_DRIVERS_ADCS_H_

#include <stdint.h>

void ADC_init_low_level(void);
void adc_read_value(uint32_t *ui32Value);

#endif /* DEVICE_DRIVERS_DRIVERS_ADCS_H_ */
