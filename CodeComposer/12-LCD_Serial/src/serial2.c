/*
 * serial2.c
 *
 *  Created on: 24 de nov de 2018
 *      Author: solid
 */

#include <serial2.h>

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"

#include <action.h>
#include <lcd16.h>


void ConfigureUart2(void)
{
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

    //    UARTIntRegister(UART2_BASE , Serial2_Handler);

    //    uint32_t ui32Status;
    //    ui32Status = UARTIntStatus(UART2_BASE, true);
    //    UARTIntClear(UART2_BASE, ui32Status);

    //    IntMasterEnable(); //enable processor interrupts
    //    IntEnable(INT_UART2); //enable the UART interrupt
    //    UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts

}
