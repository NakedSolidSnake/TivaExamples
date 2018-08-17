/*
 * uart2_driver.c
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */

#include "uart2_driver.h"
#include "device_drivers/drivers/uarts.h"

short uart2_open(){
    return 0;
}

short uart2_read(char *buf, unsigned int length){
    return 0;
}

short uart2_write(char *buf, unsigned int length){
    UART2_print((const char *)buf, length);
    return 0;
}

short uart2_ioctl(unsigned int action, void *parameter){
    return 0;
}

short uart2_close(void){
    return 0;
}
