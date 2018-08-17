/*
 * OSSystem.c
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */


#include "OSSytem.h"
#include "OSAdc.h"
#include "OSUart.h"
#include "OSTimer.h"
#include "OSDisplay.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"


void SystemInit(void){
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                           SYSCTL_OSC_MAIN);
    LCD_init();
    UART0_init();
    UART2_init();
    ADC_init();
    TIMER0_init();
}
