/*
 * main.c
 */

#include <stdint.h>
#include <string.h>
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

#include <action.h>
#include <lcd16.h>
#include <serial2.h>

#define BACKSPACE 127
#define ENTER_KEY  13

uint8_t Command_Check(uint8_t msg);

uint8_t Select_Option(const uint8_t * option);

#define BUFFER_SIZE 100
uint8_t buffer[BUFFER_SIZE] = {0};


int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );
    uint8_t rec;
    Lcd_Init();
    ConfigureUart2();
    LEDS_Init();

    Lcd_Control_Bound('>');
    (void)UARTCharGet(UART2_BASE);

    while(1)
    {
        rec = (uint8_t)UARTCharGet(UART2_BASE);
        Lcd_Control_Bound(rec);

    }
}


void Lcd_Control_Bound(uint8_t msg)
{
    static uint8_t position = 0;
    static uint8_t buffer_index = 0;
    static bool line = 1;
    uint8_t alpha = Command_Check(msg);
    if(alpha != '>')
    {
        buffer[buffer_index] = alpha;
        buffer_index++;
    }

    if(alpha != 0){
        if(position > 15)
        {
            if(line)
                line = 0;
            else
                line = 1;
            position = 0;
        }

        else{
            if(line){
                Lcd_Print_Char(alpha, LCD_LINE_1, position);
            }
            else{
                Lcd_Print_Char(alpha, LCD_LINE_2, position);
            }
            position++;
        }
    }

    else{
        //call menu
        position = 0;
        Lcd_Send(0x80, COMMAND);
        line = 1;
        Lcd_Control_Bound('>');
        Action_Select(buffer);
        memset(buffer, 0, BUFFER_SIZE);
        buffer_index = 0;
    }

}


uint8_t Command_Check(uint8_t msg)
{
    if((uint8_t)msg == BACKSPACE)
    {
        return msg;
    }

    else if((uint8_t)msg == ENTER_KEY)
    {
        Lcd_Clear();
        return 0;
    }

    else
        return msg;

}


