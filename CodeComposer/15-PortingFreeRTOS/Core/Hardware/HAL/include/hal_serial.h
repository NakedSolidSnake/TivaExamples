/*
 * hal_serial.h
 *
 *  Created on: 31 de jan de 2019
 *      Author: solid
 */

#ifndef CORE_HARDWARE_HAL_INCLUDE_HAL_SERIAL_H_
#define CORE_HARDWARE_HAL_INCLUDE_HAL_SERIAL_H_

#include <stdint.h>

typedef enum UART_DEV{
    UART_DEV0,
    UART_DEV1,
    UART_DEV2,
    UART_DEV3,
    UART_DEV4,
    UART_DEV5,
    UART_DEV6,
}UART_DEV;

typedef struct Uart_Config{
    UART_DEV dev;
    uint32_t data_bit;
    uint32_t baud_rate;
    uint32_t stop_bit;
    uint32_t parity;
}Uart_Config;


uint32_t Uart_Init(Uart_Config *uart_config);
uint32_t Uart_Write(UART_DEV uart_dev, const int8_t *buffer, uint32_t size);
uint32_t Uart_Read(UART_DEV uart_dev, int8_t *buffer, uint32_t size);
uint32_t Uart_DeInit(UART_DEV uart_dev);




#endif /* CORE_HARDWARE_HAL_INCLUDE_HAL_SERIAL_H_ */
