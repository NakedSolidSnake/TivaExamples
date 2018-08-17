/*
 * adcs.c
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */

#include <device_drivers/adc_driver.h>
#include <device_drivers/drivers/adcs.h>
#include <stdint.h>


static void adc_get_value(void *parameter){
    adc_read_value((uint32_t *)parameter);
}

typedef void (*OSAdcIOCTL)(void *parameter);

OSAdcIOCTL _adc_ioctl[] = {
     adc_get_value
};

int list_count = sizeof(_adc_ioctl)/sizeof(_adc_ioctl[0]);


static short adc_handle = ADC_CLOSED;

short adc_open(){
    ADC_ERROR adc_state = ADC_NOT_OPEN;
    if(adc_handle == ADC_CLOSED){
        adc_handle = ADC_OPEN;
        adc_state = ADC_OPEN_SECCESSFUL;
    }
    else{
        adc_state = ADC_ALREADY_OPEN;
    }
    return adc_state;
}

short adc_read(char *buf, unsigned int length){
    return 0;
}

short adc_write(char *buf, unsigned int length){
    return 0;
}

short adc_ioctl(unsigned int action, void *parameter){
    if(action < list_count){
        (*_adc_ioctl[action])(parameter);
        return 0;
    }
    return -1;
}

short adc_close(void){
    ADC_ERROR adc_state = ADC_NOT_CLOSED;
    if(adc_handle == ADC_OPEN){
        adc_handle = ADC_CLOSED;
        adc_state = ADC_CLOSE_SECCESSFUL;
    }
    else{
        adc_state = ADC_ALREADY_CLOSED;
    }
    return adc_state;
}

