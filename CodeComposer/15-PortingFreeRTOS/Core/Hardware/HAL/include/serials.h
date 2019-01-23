/*
 * serials.h
 *
 *  Created on: 13 de jan de 2019
 *      Author: solid
 */

#ifndef HAL_INCLUDE_SERIALS_H_
#define HAL_INCLUDE_SERIALS_H_

#include <stdint.h>

typedef enum SerialDev{
    SERIAL_DEV0 = 0,
    SERIAL_DEV1,
    SERIAL_DEV2,
    SERIAL_DEV3,
    SERIAL_DEV4,
    SERIAL_DEV5,
    SERIAL_DEV6
}SerialDev;

typedef void (*Serial_Handler)(void);

typedef struct SerialConfig{
    SerialDev serial_dev;               /* Serial device number */
    uint32_t baudRate;                  /* bits per second */
    Serial_Handler serial_handler;      /* function to catch interrupt */
    int8_t *buffer;                     /* Pointer to a buffer to get incoming data */
}SerialConfig;


uint8_t Serial_Init(SerialConfig *serial);
uint32_t Serial_Read(SerialDev dev, int8_t *buffer_read, uint32_t size);
uint32_t Serial_Write(SerialDev dev, int8_t *buffer_write, uint32_t size);
uint8_t Serial_DeInit(SerialDev dev);






#endif /* HAL_INCLUDE_SERIALS_H_ */
