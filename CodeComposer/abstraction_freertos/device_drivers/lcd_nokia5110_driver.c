/*
 * lcd_nokia5110_driver.c
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */


#include "lcd_nokia5110_driver.h"
#include "drivers/Nokia5110/Nokia5110.h"
#include "drivers/Nokia5110/PLL.h"

typedef void (*OSNOKIA5510IOCTL)(void *parameter);

OSNOKIA5510IOCTL _nokia5110_ioctl[] = {

};

int nokia5110_list_count = sizeof(_nokia5110_ioctl)/sizeof(_nokia5110_ioctl[0]);

short nokia5110_open(){

}

short nokia5110_read(char *buf, unsigned int length){

}

short nokia5110_write(char *buf, unsigned int length){

}

short nokia5110_ioctl(unsigned int action, void *parameter){
    if(action < nokia5110_list_count){
        (*_nokia5110_ioctl[action])(parameter);
        return 0;
    }
}

short nokia5110_close(void){

}
