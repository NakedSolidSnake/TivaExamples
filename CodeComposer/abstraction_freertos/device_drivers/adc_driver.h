/*
 * adcs.h
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_ADC_DRIVER_H_
#define DEVICE_DRIVERS_ADC_DRIVER_H_

typedef enum _ADC_STATE{
    ADC_CLOSED,
    ADC_OPEN
}ADC_STATE;

typedef enum _ADC_ERROR{
    ADC_OPEN_SECCESSFUL = 2,
    ADC_CLOSE_SECCESSFUL,
    ADC_NOT_OPEN,
    ADC_NOT_CLOSED,
    ADC_ALREADY_OPEN,
    ADC_ALREADY_CLOSED
}ADC_ERROR;



short adc_open();
short adc_read(char *buf, unsigned int length);
short adc_write(char *buf, unsigned int length);
short adc_ioctl(unsigned int action, void *parameter);
short adc_close(void);


#endif /* DEVICE_DRIVERS_ADC_DRIVER_H_ */
