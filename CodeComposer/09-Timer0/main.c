

/**
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "utils/uartstdio.h"

#define GPIO_PORTF_LOCK_R       (*((volatile uint32_t *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile uint32_t *)0x40025524))

#define UNLOCK_CODE             0x4C4F434B

#define MULT_TIMER              1

#define COM0                    0
#define BD_115200               115200
#define SYSTEM_CLK              16000000

void Timer0_Handler(void);
void PortIntHandler(void);
void ConfigureUART0(void);
void ConfigureTimer0(void);
void GPIO_IN_Init(void);
void GPIO_OUT_Init(void);

void Timer0_Handler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_3);
    UARTprintf("Green\n");
}

void PortIntHandler(void)
{
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_2);
    UARTprintf("BLUE\n");
    SysCtlDelay(2000000);
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );

    GPIO_IN_Init();
    GPIO_OUT_Init();
    ConfigureUART0();
    ConfigureTimer0();

    while(1)
    {

    }
}

void ConfigureUART0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(COM0, BD_115200, SYSTEM_CLK);
}

void ConfigureTimer0(void)
{
    unsigned long Period;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    Period = (SysCtlClockGet() * MULT_TIMER);

    TimerLoadSet(TIMER0_BASE, TIMER_A, Period - 1);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);

    IntPrioritySet(INT_TIMER0A, 0x10);
    IntEnable(INT_TIMER0A);
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
    IntPrioritySet(INT_GPIOF, 0x40);
    IntEnable(INT_GPIOF);


    return;
}

void GPIO_OUT_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1  | GPIO_PIN_2 | GPIO_PIN_3);
    return;
}
