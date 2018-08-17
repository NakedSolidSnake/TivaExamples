/*
 * OSTimer.c
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */


#include "OSTimer.h"
#include "device_drivers/drivers/timers.h"

typedef enum _TIMER_FUNCTION{
    TIMER_CLEAR_INTERRUPT,
    TIMER_LOAD_PERIOD
}TIMER_FUNCTION;

void TIMER0_init(void){
    Timer0_init_low_level();
}
