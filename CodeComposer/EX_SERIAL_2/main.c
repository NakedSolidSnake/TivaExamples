
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"

/**
 * main.c
 */
void config_serial(void);

int main(void)
{
    config_serial();

    while(1){
        //UARTCharPut(UART2_BASE, 'c');

        UARTCharGet(UART2_BASE);

        UARTprintf("Teste\n");
    }
	return 0;
}

void config_serial(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){

    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART2)){

    }


    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;
    //Configure PINs D7 and D6 as serial
    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);


    UARTClockSourceSet(UART2_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(2, 115200, 16000000);

}
