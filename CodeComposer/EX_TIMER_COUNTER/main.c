
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
void config_timer(void);

int main(void)
{
    config_timer();
    uint32_t getValue;

    while(1){
        //UARTCharPut(UART2_BASE, 'c');

        getValue = TimerValueGet(TIMER0_BASE, TIMER_A);
        if(getValue > 100){
            getValue = 0;
            TimerLoadSet(TIMER0_BASE,
            TIMER_A,
            0);
        }
    }
	return 0;
}

void config_timer(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){
    }


    GPIOPinConfigure(GPIO_PB6_T0CCP0);
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_INT_PIN_6);
    TimerConfigure(TIMER0_BASE,(TTIMER_CFG_A_CAP_COUNT_UP ));
    TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_CFG_A_CAP_COUNT_UP);
    TimerEnable(TIMER0_BASE, TIMER_A);


}
