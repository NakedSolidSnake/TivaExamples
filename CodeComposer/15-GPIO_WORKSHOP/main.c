
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

typedef struct State{
    void (*pState)(void);
}State;

static State states;

void StateOff(void);
void StateOn(void);

uint32_t Execute(State *state)
{
    if(state == ((void *) 0))
        while(1);
    if(state->pState == ((void *) 0))
        while(1);
    else
        state->pState();
}

void StateOn(void)
{
    static uint8_t ui8PinData = 2;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, ui8PinData);
    SysCtlDelay(2000000);
    if(ui8PinData == 8)
    {
        ui8PinData = 2;
    }
    else{
        ui8PinData *= 2;
    }
    states.pState = StateOff;
    return ;
}

void StateOff(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
    SysCtlDelay(2000000);
    states.pState = StateOn;
    return;
}



/**
 * main.c
 */
int main(void)
{

    states.pState = StateOn;

    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);


    while(1)
    {
        Execute(&states);

    }
	return 0;
}
