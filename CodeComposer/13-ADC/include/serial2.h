/*
 * serial2.h
 *
 *  Created on: 24 de nov de 2018
 *      Author: solid
 */

#ifndef INCLUDE_SERIAL2_H_
#define INCLUDE_SERIAL2_H_


#include <stdint.h>

void ConfigureUart2(void);
uint8_t Uart2_Get_Char(void);
void Uart2_Put_Char(uint8_t character);
void Uart2_Print(uint8_t *wBuffer, uint32_t size);


#endif /* INCLUDE_SERIAL2_H_ */
