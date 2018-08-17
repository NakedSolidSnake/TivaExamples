/*
 * timers.c
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"
#include "timers.h"

void Timer0_ClearInterrupt(void){
    TimerIntClear(TIMER0_BASE,
                      TIMER_TIMA_TIMEOUT);
}

void Timer0_set_value(uint32_t period){
    TimerLoadSet(TIMER0_BASE, TIMER_A, period -1);
}

extern void timerA_interrupt_handler(void);

void Timer0_init_low_level(void){
    uint32_t Period;
    Period = 80000; //1ms
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){
    }



    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, Period -1);
    TimerIntRegister(TIMER0_BASE,
                     TIMER_A,
                     timerA_interrupt_handler);

   // TimerIntEnable(TIMER0_BASE,
     //           TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER0_BASE, TIMER_A);

}
