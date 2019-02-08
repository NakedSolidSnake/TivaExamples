/*
 * sfa_lcd.h
 *
 *  Created on: 11 de jan de 2019
 *      Author: solid
 */

#ifndef APPLICATION_SFA_SFA_LCD_SFA_LCD_H_
#define APPLICATION_SFA_SFA_LCD_SFA_LCD_H_

#include <stdint.h>

int8_t SFA_LCD_Init(void);
int8_t SFA_LCD_Write(const char *msg, int8_t line, uint8_t offset);


#endif /* APPLICATION_SFA_SFA_LCD_SFA_LCD_H_ */
