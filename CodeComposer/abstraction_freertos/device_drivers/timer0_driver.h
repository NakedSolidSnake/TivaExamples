/*
 * timer0_driver.h
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_TIMER0_DRIVER_H_
#define DEVICE_DRIVERS_TIMER0_DRIVER_H_

short timer0_open();
short timer0_read(char *buf, unsigned int length);
short timer0_write(char *buf, unsigned int length);
short timer0_ioctl(unsigned int action, void *parameter);
short timer0_close(void);

#endif /* DEVICE_DRIVERS_TIMER0_DRIVER_H_ */
