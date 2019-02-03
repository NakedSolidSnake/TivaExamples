/*
 * driver_serial.h
 *
 *  Created on: 31 de jan de 2019
 *      Author: solid
 */

#ifndef CORE_HARDWARE_DEVICEDRIVER_INCLUDE_DRIVER_SERIAL_H_
#define CORE_HARDWARE_DEVICEDRIVER_INCLUDE_DRIVER_SERIAL_H_


/* include *******************************************************************************************/
#include <stdint.h>

/* defines *******************************************************************************************/

/* enumerations **************************************************************************************/

/* structures ****************************************************************************************/
typedef struct Serial_Descriptor{
    uint8_t dev;
    uint32_t baudrate;
    uint32_t stopbits;
    uint32_t parity;
    uint32_t databits;
}Serial_Descriptor;

/* public functions **********************************************************************************/
int8_t  serial_open (const void *context);
int32_t serial_write(const void *context, const void *buffer_write, uint32_t size);
int32_t serial_read (const void *context, void *buffer_read, uint32_t *size);
int8_t  serial_ioctl(const void *context, uint8_t command, void *args);
int8_t  serial_close(const void *context);


#endif /* CORE_HARDWARE_DEVICEDRIVER_INCLUDE_DRIVER_SERIAL_H_ */
