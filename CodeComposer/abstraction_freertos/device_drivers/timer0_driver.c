/*
 * timer0_driver.c
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */

#include "timer0_driver.h"
#include "drivers/timers.h"
#include <stdint.h>

static void timer_clear_interrupt(void *parameter){
    Timer0_ClearInterrupt();
}

static void timer_load_period(void *parameter){
    Timer0_set_value((uint32_t *)parameter);
}

typedef void (*OSTIMERSIOCTL)(void *parameter);

OSTIMERSIOCTL _timer_ioctl[] = {
     timer_clear_interrupt,
     timer_load_period
};

int timer_list_count = sizeof(_timer_ioctl)/sizeof(_timer_ioctl[0]);


short timer0_open(){
    return 0;
}

short timer0_read(char *buf, unsigned int length){
    return 0;
}

short timer0_write(char *buf, unsigned int length){

    return 0;
}

short timer0_ioctl(unsigned int action, void *parameter){
    if(action < timer_list_count){
           (*_timer_ioctl[action])(parameter);
           return 0;
       }
    return 0;
}

short timer0_close(void){
    return 0;
}
