/*
 * OSDisplay.c
 *
 *  Created on: 7 de dez de 2017
 *      Author: solid
 */


#include "OSDisplay.h"
#include "device_drivers/drivers/Nokia5110/Nokia5110.h"
#include "device_drivers/drivers/Nokia5110/PLL.h"

void LCD_init(void){
    PLL_Init();
    Nokia5110_Init();
}
