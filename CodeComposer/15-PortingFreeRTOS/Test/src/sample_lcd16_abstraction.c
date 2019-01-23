/*
 * sample_lcd16_abstraction.c
 *
 *  Created on: 22 de jan de 2019
 *      Author: solid
 */


#include "test.h"
#include <stdint.h>
#include "fileoperation.h"

int Test_LCD16_Abstraction(void)
{
    int8_t lcd_handle = device_open("LCD16");

    if(lcd_handle < 0)
        return 1;

    device_write(lcd_handle, "Test LCD", 0);

    device_close(lcd_handle);
}

