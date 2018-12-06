/*
 * serial2.h
 *
 *  Created on: 24 de nov de 2018
 *      Author: solid
 */

#ifndef INCLUDE_SERIAL2_H_
#define INCLUDE_SERIAL2_H_

#include <stdint.h>

void Uart2Configure(void);
uint32_t Uart2_Print(const char *string, uint32_t size);

#endif /* INCLUDE_SERIAL2_H_ */
