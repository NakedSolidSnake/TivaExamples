/*
 * uarts.h
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */

#ifndef DEVICE_DRIVERS_DRIVERS_UARTS_H_
#define DEVICE_DRIVERS_DRIVERS_UARTS_H_

void UART0_init_low_level(void);
void UART2_init_low_level(void);

void UART0_print(const char *szname, unsigned int lenght);
void UART2_print(const char *szname, unsigned int lenght);

#endif /* DEVICE_DRIVERS_DRIVERS_UARTS_H_ */
