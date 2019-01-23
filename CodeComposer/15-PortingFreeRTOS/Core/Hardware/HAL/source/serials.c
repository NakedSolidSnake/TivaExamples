/*
 * serials.c
 *
 *  Created on: 13 de jan de 2019
 *      Author: solid
 */

#include "serials.h"

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



static uint8_t Serial_Set_BaudRate(SerialConfig *serial)
{
    return 0;
}

static uint8_t ConfigureUART2(SerialConfig *serial)
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
    return 0;
}

uint8_t Serial_Init(SerialConfig *serial)
{

}

uint32_t Serial_Read(SerialDev dev, int8_t *buffer_read, uint32_t size)
{

}

uint32_t Serial_Write(SerialDev dev, int8_t *buffer_write, uint32_t size)
{

}

uint8_t Serial_DeInit(SerialDev dev)
{

}



