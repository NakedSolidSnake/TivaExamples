/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "utils/uartstdio.h"

#define GPIO_PORTF_LOCK_R       (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile uint32_t *)0x40025524))

#define UNLOCK_CODE             0x4C4F434B

#define COM0            0
#define BD_115200       115200
#define SYSTEM_CLK      16000000


void ConfigureUART(void);

void PortIntHandler(void)
{
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_2);
    UARTprintf("BLUE\n");
    SysCtlDelay(2000000);
}

void ConfigureUART(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(COM0, BD_115200, SYSTEM_CLK);
}


void Config_Int(void);
void GPIO_IN_Init(void);


int main(void) {
    int32_t readKey = 0;

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );
    GPIO_OUT_Init();
    GPIO_IN_Init();
    ConfigureUART();

    while(1)
    {
        readKey = GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_0  | GPIO_PIN_4);
        if((readKey & 0x01) != 0x01 )
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1  | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1);
            UARTprintf("RED\n");
        }
        else{
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1  | GPIO_PIN_2 | GPIO_PIN_3, 0);
        }
    }

    return 0;
}


void GPIO_OUT_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1  | GPIO_PIN_2 | GPIO_PIN_3);
    return;
}

void GPIO_IN_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIO_PORTF_LOCK_R = UNLOCK_CODE;
    GPIO_PORTF_CR_R = 0x1F;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0  | GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0  | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
    IntEnable(INT_GPIOF);


    return;
}

