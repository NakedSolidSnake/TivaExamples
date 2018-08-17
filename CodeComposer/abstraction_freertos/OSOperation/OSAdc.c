/*
 * OSAdc.c
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */

#include <device_drivers/adc_driver.h>
#include "OSAdc.h"
#include "device_drivers/drivers/adcs.h"

typedef enum _ADC_IOCTL{
    ADC_GET_VALUE,
}ADC_IOCTL;


void ADC_init(void){
    ADC_init_low_level();
}
