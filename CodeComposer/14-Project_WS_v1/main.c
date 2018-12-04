

/**
 * main.c
 */

#include <fileoperation.h>
#include <stdint.h>

int main(void)
{
    const char *b = "Cristiano";
    int8_t lcd_handle = device_open("LCD16");
    device_write(lcd_handle, b, 9);

    while(1);
	return 0;
}
