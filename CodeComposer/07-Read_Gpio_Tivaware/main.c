/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"



void GPIO_OUT_Init(void);
void GPIO_IN_Init(void);


int main(void) {
    int32_t readKey = 0;

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );
    GPIO_OUT_Init();
    GPIO_IN_Init();

    while(1)
    {
        readKey = GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_0  | GPIO_PIN_4);
        if((readKey & 0x10) != 0x10 )
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1  | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1);
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
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0  | GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0  | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    return;
}

