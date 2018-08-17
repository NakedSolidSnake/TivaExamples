/*
 * uart.h
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_UART0_DRIVER_H_
#define DEVICE_DRIVERS_UART0_DRIVER_H_

short uart0_open();
short uart0_read(char *buf, unsigned int length);
short uart0_write(char *buf, unsigned int length);
short uart0_ioctl(unsigned int action, void *parameter);
short uart0_close(void);

#endif /* DEVICE_DRIVERS_UART0_DRIVER_H_ */
