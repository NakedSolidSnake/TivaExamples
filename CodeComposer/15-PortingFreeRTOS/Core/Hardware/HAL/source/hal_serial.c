/*
 * hal_serial.c
 *
 *  Created on: 31 de jan de 2019
 *      Author: solid
 */

#include "hal_serial.h"

#include <stdbool.h>
#include <stdlib.h>

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

static uint32_t Uart_Get_Base(uint32_t dev)
{
    uint32_t base_addr = 0;
    switch (dev) {
    case 0:
        base_addr = UART0_BASE;
        break;
    case 1:
        base_addr = UART1_BASE;
        break;
    case 2:
        base_addr = UART2_BASE;
        break;
    case 3:
        base_addr = UART3_BASE;
        break;
    case 4:
        base_addr = UART4_BASE;
        break;
    case 5:
        base_addr = UART5_BASE;
        break;
    case 6:
        base_addr = UART6_BASE;
        break;
    case 7:
        base_addr = UART7_BASE;
        break;
    default:
        break;
    }
    return base_addr;
}

static void Uart_Clock_Enable(uint32_t dev)
{
    switch (dev) {
        case 2:
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){

            }
            SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART2)){

            }
            break;
        default:
            break;
    }
}

static void Uart_GPIO_Config(uint32_t dev)
{
    switch (dev) {
        case 2:
            HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
            HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;
            //Configure PINs D7 and D6 as serial
            GPIOPinConfigure(GPIO_PD6_U2RX);
            GPIOPinConfigure(GPIO_PD7_U2TX);
            GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

            break;
        default:
            break;
    }
}

static void Uart_Get_DataBits(uint32_t *databits)
{
    if(databits)
    {
        if(*databits == 8)
        {
            *databits = UART_CONFIG_WLEN_8;
        }
    }
}

static void Uart_Get_StopBits(uint32_t *stopbits)
{
    if(stopbits)
    {
        if(*stopbits == 1)
        {
            *stopbits = UART_CONFIG_STOP_ONE;
        }
    }
}

static void Uart_Get_Parity(uint32_t *parity)
{
    if(parity)
    {
        if(*parity == 0)
        {
            *parity = UART_CONFIG_PAR_NONE;
        }
    }
}



uint32_t Uart_Init(Uart_Config *uart_config)
{
    uint32_t uart_base;
    if(uart_config == NULL)
        return 1;

    uart_base = Uart_Get_Base((uint32_t)uart_config->dev);
    Uart_Get_DataBits(&uart_config->data_bit);
    Uart_Get_StopBits(&uart_config->stop_bit);
    Uart_Get_Parity(&uart_config->parity);

    Uart_Clock_Enable((uint32_t)uart_config->dev);

    UARTConfigSetExpClk(uart_base, SysCtlClockGet(),
                        uart_config->baud_rate,
                        uart_config->data_bit |
                        uart_config->stop_bit |
                        uart_config->parity);


    Uart_GPIO_Config((uint32_t)uart_config->dev);
    (void)UARTCharGet(uart_base);

    return 0;
}

uint32_t Uart_Write(UART_DEV uart_dev, const int8_t *buffer, uint32_t size)
{
    uint32_t writeCount = 0, uart_base;
    uart_base = Uart_Get_Base((uint32_t)uart_dev);

    if(buffer == NULL || size == 0)
    {
        return 0;
    }


    for(int i = 0; i < size; i++)
    {
        UARTCharPut(uart_base, *(buffer + i));
    }

    return writeCount;
}

uint32_t Uart_Read(UART_DEV uart_dev, int8_t *buffer, uint32_t size)
{
    uint32_t readCount = 0, uart_base;
    uart_base = Uart_Get_Base((uint32_t)uart_dev);
    if(buffer == NULL || size == 0)
    {
        return 0;
    }

    for(int i = 0; i < size; i++ )
    {
        buffer[i] = UARTCharGet(uart_base);
        readCount++;
    }

    return readCount;
}

uint32_t Uart_DeInit(UART_DEV uart_dev)
{
    return 0;
}

