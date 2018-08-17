/*
 * uarts.c
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */

#include <device_drivers/uart0_driver.h>
#include "device_drivers/drivers/uarts.h"

short uart0_open(){

    return 0;
}

short uart0_read(char *buf, unsigned int length){

    return 0;
}

short uart0_write(char *buf, unsigned int length){
    UART0_print((const char *)buf, length);
    return 0;
}

short uart0_ioctl(unsigned int action, void *parameter){

    return 0;
}

short uart0_close(void){
    return 0;
}

