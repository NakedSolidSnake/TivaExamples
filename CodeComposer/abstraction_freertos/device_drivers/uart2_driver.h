/*
 * uart2_driver.h
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_UART2_DRIVER_H_
#define DEVICE_DRIVERS_UART2_DRIVER_H_

short uart2_open();
short uart2_read(char *buf, unsigned int length);
short uart2_write(char *buf, unsigned int length);
short uart2_ioctl(unsigned int action, void *parameter);
short uart2_close(void);

#endif /* DEVICE_DRIVERS_UART2_DRIVER_H_ */
