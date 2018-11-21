
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#define COM0            0
#define BD_115200       115200
#define SYSTEM_CLK      16000000


#define TRUE            1

#define RX_BUF_LEN 100

void ConfigureUART(void);

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

/**
 * main.c
 */
int main(void)
{
    char buffer[RX_BUF_LEN] = {0};
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);

    ConfigureUART();

    while(TRUE)
    {
        UARTprintf("Send me any char\r\n");
        SysCtlDelay(1000000);
        UARTgets(buffer, sizeof(buffer));
        UARTprintf("Received.:");
        UARTprintf(buffer);
        UARTprintf("\r\n");
    }
	return 0;
}
