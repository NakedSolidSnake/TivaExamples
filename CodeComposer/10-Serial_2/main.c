/*
 * main.c
 */

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"


#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"

#define STX 0x02
#define ETX 0x03

#define BUFFER_SIZE 100

#define LED_RED   GPIO_PIN_1
#define LED_BLUE  GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3

void Serial2_Handler(void);
void ConfigureUart2(void);
void Serial2_print(const char *msg);
void GPIO_OUT_Init(void);

uint32_t rec = 0;


static char protocol[BUFFER_SIZE];
bool recv_flag = 0, complete = 0;
char count = 0;

void Serial2_Handler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART2_BASE, true);
    UARTIntClear(UART2_BASE, ui32Status);
    while(UARTCharsAvail(UART2_BASE))
    {
        rec = (unsigned char)UARTCharGetNonBlocking(UART2_BASE);
        if(rec == STX)
        {
            recv_flag = 1;
            rec = 0;
        }

        else if(recv_flag)
        {
            if(rec == ETX || count > sizeof(protocol))
            {
                count = 0;
                rec = 0;
                recv_flag = 0;
                complete = 1;
            }
            else{
                protocol[count] = rec;
                count++;
            }
        }
    }
}

int main(void) {
	
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );

    ConfigureUart2();
    GPIO_OUT_Init();

    while(1)
    {
        if(complete)
        {
            Serial2_print("OK!\n");
            Serial2_print(protocol);

            if(!strcmp(protocol, "RED"))
            {
                GPIOPinWrite(GPIO_PORTF_BASE, LED_RED  | LED_BLUE | LED_GREEN, LED_RED);
                Serial2_print("LED RED ON!\n");
            }

            if(!strcmp(protocol, "GREEN"))
            {
                GPIOPinWrite(GPIO_PORTF_BASE, LED_RED  | LED_BLUE | LED_GREEN, LED_GREEN);
                Serial2_print("LED GREEN ON!\n");
            }

            if(!strcmp(protocol, "BLUE"))
            {
                GPIOPinWrite(GPIO_PORTF_BASE, LED_RED  | LED_BLUE | LED_GREEN, LED_BLUE);
                Serial2_print("LED BLUE ON!\n");
            }

            if(!strcmp(protocol, "OFF"))
            {
                GPIOPinWrite(GPIO_PORTF_BASE, LED_RED  | LED_BLUE | LED_GREEN, 0);
                Serial2_print("LEDS OFF!\n");
            }

            memset(protocol, 0, sizeof(protocol));
            complete = 0;
        }
    }


}


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

    UARTIntRegister(UART2_BASE , Serial2_Handler);

    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART2_BASE, true);
    UARTIntClear(UART2_BASE, ui32Status);

    IntMasterEnable(); //enable processor interrupts
    IntEnable(INT_UART2); //enable the UART interrupt
    UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts

}

void Serial2_print(const char *msg){
    const char *ptr = msg;
    for(; *ptr != '\0'; ptr++){
        UARTCharPut(UART2_BASE, *ptr);
    }
}

void GPIO_OUT_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1  | GPIO_PIN_2 | GPIO_PIN_3);
    return;
}
