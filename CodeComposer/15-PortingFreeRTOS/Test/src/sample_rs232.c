/*
 * sample_rs232.c
 *
 *  Created on: 2 de fev de 2019
 *      Author: solid
 */


#include "test.h"
//#include "hal_serial.h"
#include <string.h>
#include "fileoperation.h"


int Test_RS232_Driver(void)
{
    const char *msg = "Test Serial 2\n";
    char buffer[5];

#if 0
    Uart_Config uart_cfg = {
                            .baud_rate = 115200,
                            .data_bit = 8,
                            .dev = UART_DEV2,
                            .parity = 0,
                            .stop_bit = 1
    };

    Uart_Init(&uart_cfg);
    Uart_Write(uart_cfg.dev, msg, (uint32_t)strlen(msg));
    Uart_Read(uart_cfg.dev, buffer, (uint32_t)sizeof(buffer));
    Uart_Write(uart_cfg.dev, buffer, (uint32_t)strlen(buffer));
#endif


#if 0
    int8_t fd = device_open("Serial2");
    uint32_t buf_size = (uint32_t)sizeof(buffer);

    device_write(fd, msg, (uint32_t)strlen(msg));
    device_read(fd, buffer, &buf_size);
    device_write(fd, buffer, (uint32_t)strlen(buffer));

#endif
}
