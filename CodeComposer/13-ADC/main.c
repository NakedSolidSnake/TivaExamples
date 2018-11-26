

/**
 * main.c
 */

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include <ADC.h>
#include <serial2.h>

#include "inc/hw_sysctl.h"
#include "driverlib/sysctl.h"

#define BUFFER_SIZE 50

const uint8_t *start_message = "Welcome\n\r";

int main(void)
{
    uint8_t buffer_write[BUFFER_SIZE] = {0};
    uint32_t ad_read = 0;

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    ConfigureUart2();
    ADC_Init();
    Uart2_Print(start_message, strlen(start_message));

    while(1)
    {
        ad_read = ADC_Read();
        sprintf((char *)buffer_write, "ADC Value = %d\n\r", ad_read);
        Uart2_Print(buffer_write, strlen(buffer_write));
        memset(buffer_write, 0 , BUFFER_SIZE);

    }

	return 0;
}
