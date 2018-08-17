/*
 * hal_uart.c
 *
 *  Created on: 2 de dez de 2017
 *      Author: solid
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "hal_uart.h"

void config_serial(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){

    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART2)){

    }

    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200,
                       (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                        UART_CONFIG_PAR_NONE));


    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;
    //Configure PINs D7 and D6 as serial
    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
}


void print(const char *szname){

    char *ptr = szname;
    for(; *ptr != '\0'; ptr++){
        UARTCharPut(UART2_BASE, *ptr);
    }
}
