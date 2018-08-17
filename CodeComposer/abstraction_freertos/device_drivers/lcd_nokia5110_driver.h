/*
 * lcd_nokia5110_driver.h
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_LCD_NOKIA5110_DRIVER_H_
#define DEVICE_DRIVERS_LCD_NOKIA5110_DRIVER_H_

short nokia5110_open();
short nokia5110_read(char *buf, unsigned int length);
short nokia5110_write(char *buf, unsigned int length);
short nokia5110_ioctl(unsigned int action, void *parameter);
short nokia5110_close(void);

#endif /* DEVICE_DRIVERS_LCD_NOKIA5110_DRIVER_H_ */
