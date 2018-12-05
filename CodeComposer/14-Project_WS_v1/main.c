

/**
 * main.c
 */

#include <fileoperation.h>
#include <Framework/LCD16_IOCTL.h>
#include <stdint.h>
#include <stdlib.h>

int main(void)
{
    const char *b = "Cristiano";
    int8_t lcd_handle = device_open("LCD16");
    device_write(lcd_handle, b, 9);
    device_ioctl(lcd_handle, LCD_LINE_SET_2, NULL);
    device_write(lcd_handle, b, 9);
    while(1);
	return 0;
}
