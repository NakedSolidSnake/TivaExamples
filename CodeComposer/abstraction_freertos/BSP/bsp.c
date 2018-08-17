/*
 * test.c
 *
 *  Created on: 2 de dez de 2017
 *      Author: solid
 */


#include <device_drivers/uart0_driver.h>
#include <device_drivers/uart2_driver.h>
#include "OSOperation/OSOperation.h"
#include "device_drivers/adc_driver.h"
#include "device_drivers/lcd_nokia5110_driver.h"
#include "device_drivers/timer0_driver.h"

OSOperation mydev[]= {
                         {"ADC",   .open = adc_open,   .read = adc_read,   .write = adc_write,   .ioctl = adc_ioctl,   .close = adc_close},
                         {"UART0", .open = uart0_open, .read = uart0_read, .write = uart0_write, .ioctl = uart0_ioctl, .close = uart0_close},
                         {"UART2", .open = uart2_open, .read = uart2_read, .write = uart2_write, .ioctl = uart2_ioctl, .close = uart2_close},
                         {"LCD",   .open = nokia5110_open, .read = nokia5110_read, .write = nokia5110_write, .ioctl = nokia5110_ioctl, .close = nokia5110_close},
                         {"TIMER0",   .open = timer0_open, .read = timer0_read, .write = timer0_write, .ioctl = timer0_ioctl, .close = timer0_close},


};


int OS_lenght = sizeof(mydev)/ sizeof(mydev[0]);
OSOperation *__OSOperation = mydev;

