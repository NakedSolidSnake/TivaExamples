/*
 * lcd16.h
 *
 *  Created on: 24 de nov de 2018
 *      Author: solid
 */

#ifndef INCLUDE_LCD16_H_
#define INCLUDE_LCD16_H_

#include <stdint.h>

#define LCD_COMMAND_LINE_1          0x80
#define LCD_COMMAND_LINE_2          0xC0
#define LCD_COMMAND_CLEAR           0x01


typedef enum LCD_MODE_TAG{
    COMMAND,
    MESSAGE
}LCD_MODE;

typedef enum LCD_LINE_TAG{
    LCD_LINE_1,
    LCD_LINE_2
}LCD_LINE;


void Lcd_Init(void);
void LCD_Print_Char(const char letter);
void LCD_Print(const char *message);
void Lcd_Send(unsigned char data, LCD_MODE lcd_mode);
void Lcd_Print_Char(const char letter, LCD_LINE line, int offset);
void Lcd_Print(const char *message, LCD_LINE line, int offset);
void Lcd_Send_All(const char * data_line1, const char *data_line2);
void delayMs(int n);
void Lcd_Create(void);
void Lcd_Clear(void);
void Lcd_Control_Bound(uint8_t msg);


#endif /* INCLUDE_LCD16_H_ */
