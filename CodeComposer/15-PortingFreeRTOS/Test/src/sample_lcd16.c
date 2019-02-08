/*
 * sample_lcd16.c
 *
 *  Created on: 9 de jan de 2019
 *      Author: solid
 */

#if 0

#include "test.h"
#include "lcd16.h"


int Test_LCD16(void)
{
    Lcd_Init();

    Lcd_Print("  Hello World!  ", LCD_LINE_1, 0);
    Lcd_Print("!!! Test LCD !!!", LCD_LINE_2, 0);

    return 0;
}

#endif
