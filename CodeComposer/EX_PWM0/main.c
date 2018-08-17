
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/timer.h"

/**
 * main.c
 */
void config_pwm(void);
void config_timer(void);

int main(void)
{
    volatile uint32_t timerGet = 0;
    config_pwm();
    config_timer();
    while(1){
        timerGet = TimerValueGet(TIMER0_BASE, TIMER_A);

    }
	return 0;
}

void config_pwm(void){

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinConfigure(GPIO_PC4_M0PWM6);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);

    /*SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        GPIOPinConfigure(GPIO_PB6_M0PWM0);
        GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);*/

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){

    }

    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 100);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 90);

    PWMGenEnable(PWM0_BASE, PWM_GEN_3);

    PWMOutputState(PWM0_BASE, (PWM_OUT_6_BIT ), true);

  //  while(1);
}

void config_timer(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){
    }


    GPIOPinConfigure(GPIO_PB6_T0CCP0);
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_CAP_COUNT );

    TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_BOTH_EDGES);

    TimerEnable(TIMER0_BASE, TIMER_A);

}
