

/**
 * main.c
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "inc/hw_gpio.h"
#include "utils/uartstdio.h"

#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

#include <string.h>

#define STX 0x02
#define ETX 0x03

static unsigned int control = 0;

typedef enum ProtocolState{
    PROTOCOL_GET_STX,
    PROTOCOL_GET_COMMAND,
    PROTOCOL_GET_PAYLOAD,
    PROTOCOL_GET_ETX,
}ProtocolState;

static ProtocolState smProtocol = PROTOCOL_GET_STX;



int Protocol_Get(unsigned char *buffer);

static uint8_t rec = 0;

void Serial2_Handler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART2_BASE, true);
    UARTIntClear(UART2_BASE, ui32Status);
    while(UARTCharsAvail(UART2_BASE))
    {
        rec = (unsigned char)UARTCharGetNonBlocking(UART2_BASE);
    }
}

static void Serial2_init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART2)){}

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
//
//    uint32_t ui32Status;
//    ui32Status = UARTIntStatus(UART2_BASE, true);
//    UARTIntClear(UART2_BASE, ui32Status);
//
//    IntMasterEnable(); //enable processor interrupts
//    IntEnable(INT_UART2); //enable the UART interrupt
//    UARTIntEnable(UART2_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
}

unsigned char Serial_Get_Char()
{
    unsigned char getChar = 0;

    rec  = (uint8_t)UARTCharGet(UART2_BASE);
    if(rec != 0)
    {
        getChar = rec;
        rec = 0;
    }

    return getChar;
}

static void Serial2_print(const char *msg){
    const char *ptr = msg;
    for(; *ptr != '\0'; ptr++){
        UARTCharPut(UART2_BASE, *ptr);
    }
}



/***************************************************************************************************/

int Protocol_Get(unsigned char *buffer)
{
    unsigned ret = 1;
    switch (smProtocol) {
        case PROTOCOL_GET_STX:
            if(Serial_Get_Char() == STX)
            {
                smProtocol = PROTOCOL_GET_COMMAND;
                control = 0;
            }
            break;

        case PROTOCOL_GET_COMMAND:
            for(; control < 2; control++)
            {
                buffer[control] = Serial_Get_Char();
            }
            smProtocol = PROTOCOL_GET_PAYLOAD;
            break;

        case PROTOCOL_GET_PAYLOAD:
            for(; control < 6; control++)
            {
                buffer[control] = Serial_Get_Char();
            }
            smProtocol = PROTOCOL_GET_ETX;
            break;

        case PROTOCOL_GET_ETX:
            if(Serial_Get_Char() == ETX)
            {
                smProtocol = PROTOCOL_GET_STX;
                control = 0;
                ret = 0;
            }
            break;
        default:
            break;
    }
    return ret;
}

int main(void)
{
    unsigned char temp[10];
    Serial2_init();

    while(1)
    {
        while(Protocol_Get(temp));
        Serial2_print((const char *)temp);
    }

}
