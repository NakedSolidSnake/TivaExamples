/*
 * OSUart.c
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */


#include "OSUart.h"
#include "device_drivers/drivers/uarts.h"

void UART0_init(void){
    UART0_init_low_level();
}

void UART2_init(void){
    UART2_init_low_level();
}
