/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "driverlib/pin_map.h"

#define RS  GPIO_PIN_2
#define EN  GPIO_PIN_3
#define DB4 GPIO_PIN_4
#define DB5 GPIO_PIN_5
#define DB6 GPIO_PIN_6
#define DB7 GPIO_PIN_7

#define LCD_BASE GPIO_PORTA_BASE

#define HIGH 1
#define LOW  0

typedef enum LCD_MODE_TAG{
    COMMAND,
    MESSAGE
}LCD_MODE;

typedef enum LCD_LINE_TAG{
    LCD_LINE_1,
    LCD_LINE_2
}LCD_LINE;

void Lcd_Init(void);
void Lcd_Send(unsigned char data, LCD_MODE lcd_mode);
void Lcd_Print(const char *message, LCD_LINE line, int offset);
void Lcd_Send_All(const char * data_line1, const char *data_line2);
void delayMs(int n);
void Lcd_Create(void);

int main(void) {
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );
    Lcd_Init();

    Lcd_Print("Test LCD", LCD_LINE_1, 0);
    Lcd_Print("LCD Driver", LCD_LINE_2, 0);

    while(1);

	return 0;
}

void Lcd_Init(void)
{
    //Configure Gpio
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){
    }

    //Configure Gpio
    GPIOPinTypeGPIOOutput(LCD_BASE, RS | EN | DB4 | DB5 | DB6 | DB7);


    delayMs(20);
    Lcd_Send(0x02, COMMAND);
    Lcd_Send(0x03, COMMAND);
    Lcd_Send(0x28, COMMAND);
    Lcd_Send(0x06, COMMAND);
    Lcd_Send(0x0C, COMMAND);
    Lcd_Send(0x01, COMMAND);
}

void Lcd_Send(unsigned char data, LCD_MODE lcd_mode) {
//    LCD_ready();
    switch (lcd_mode) {
    case COMMAND:
        GPIOPinWrite(LCD_BASE, RS, LOW);
        break;

    case MESSAGE:
        GPIOPinWrite(LCD_BASE, RS, RS);
        break;
    }

    //Pass data to LCD_DATA_REGISTER
    GPIOPinWrite(LCD_BASE, DB7 | DB6 | DB5| DB4, data);
    GPIOPinWrite(LCD_BASE, EN, EN);
    delayMs(10);
    GPIOPinWrite(LCD_BASE, EN, LOW);
    GPIOPinWrite(LCD_BASE, DB7 | DB6 | DB5| DB4, data << 4);
    GPIOPinWrite(LCD_BASE, EN, EN);
    delayMs(10);
    GPIOPinWrite(LCD_BASE, EN, LOW);
}

void Lcd_Print(const char *message, LCD_LINE line, int offset)
{
    switch (line) {
    case LCD_LINE_1:
        Lcd_Send(0x80 + offset, COMMAND);
        break;
    case LCD_LINE_2:
        Lcd_Send(0xC0 + offset, COMMAND);
        break;
    }
    for (; *message != '\0'; message++) {
        Lcd_Send(*message, MESSAGE);
    }
}


void Lcd_Send_All(const char * data_line1, const char *data_line2)
{
    Lcd_Print(data_line1, LCD_LINE_1, 0);
    Lcd_Print(data_line2, LCD_LINE_2, 0);
}

void delayMs(int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 1075; j++)
            ;
}

void Lcd_Create(void)
{
    char new_char[] = {0x10, 0x18, 0x1c, 0x1e, 0x1e, 0x1c, 0x18, 0x10};
    uint8_t i;
    Lcd_Send(0x40, COMMAND);
    for (i = 0; i < 8; i++) {
        Lcd_Send(new_char[i], MESSAGE);
    }
}
