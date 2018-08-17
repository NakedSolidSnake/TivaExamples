
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"

/**
 * main.c
 */

int32_t one_Second = 0;

void timerA_interrupt_handler(void){
    static int counter = 0;

    counter++;

    if(counter == 10){
        counter = 0;
        one_Second++;
    }
}

void config_timer(void);

int main(void)
{
    config_timer();


    while(1){
        //UARTCharPut(UART2_BASE, 'c');




    }
    return 0;
}

void config_timer(void){
    uint32_t Period;
      Period = 80000; //1ms
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){
    }



    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, Period -1);
    TimerIntRegister(TIMER0_BASE,
                         TIMER_A,
                         timerA_interrupt_handler);

      TimerIntEnable(TIMER0_BASE,
                   TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER0_BASE, TIMER_A);


}
