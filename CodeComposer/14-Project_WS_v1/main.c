

/**
 * main.c
 */

#include <fileoperation.h>
#include <Framework/LCD16_IOCTL.h>
#include <stdint.h>
#include <stdlib.h>

void test_LCD(void);
void test_Serial(void);
void test_ADC(void);


int main(void)
{

//    test_LCD();
//    test_Serial();
    test_ADC();
    while(1);
    return 0;
}

void test_LCD(void)
{
    const char *b = "Cristiano";
    int8_t lcd_handle = device_open("LCD16");
    device_write(lcd_handle, b, 9);
    device_ioctl(lcd_handle, LCD_LINE_SET_2, NULL);
    device_write(lcd_handle, b, 9);
}


void test_Serial(void)
{
    const char *b = "Cristiano";
    int8_t serial_handle = device_open("SERIAL");
    device_write(serial_handle, b, 9);
}

void test_ADC(void)
{
    const char *b = "Cristiano";
    uint8_t read[4];
    int8_t adc_handle = device_open("ADC");
    device_read(adc_handle, &read, 4);

}
