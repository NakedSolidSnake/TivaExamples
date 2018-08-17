/*
 * OSOperation.c
 *
 *  Created on: 2 de dez de 2017
 *      Author: solid
 */

#include "OSOperation.h"
#include <string.h>


extern OSOperation *__OSOperation;
extern int OS_lenght;


short dev_open(const char *dev){
    int index;
    for(index = 0; index < OS_lenght; index++){
        if(!strcmp(__OSOperation[index].name, dev)){
            if(!__OSOperation[index].isOpen || __OSOperation[index].open() >= 0){
                __OSOperation[index].isOpen = 1;
                return index;
            }
            return -1;
        }
    }
    return -1;
}

short dev_read(short handle, char *buf, unsigned int lenght){

    if(handle >= 0 && handle < OS_lenght && __OSOperation[handle].isOpen){
        return __OSOperation[handle].read(buf, lenght);
    }
    return -1;
}

short dev_write(short handle, char *buf, unsigned int lenght){
    if(handle >= 0 && handle < OS_lenght && __OSOperation[handle].isOpen){
            return __OSOperation[handle].write(buf, lenght);
        }
        return -1;
}

short dev_ioctl(short handle, unsigned int option, void *parameter){
    if(handle >= 0 && handle < OS_lenght && __OSOperation[handle].isOpen){
            return __OSOperation[handle].ioctl(option, parameter);
        }
        return -1;
}

short dev_close(short handle){
    if(__OSOperation[handle].isOpen && handle >= 0 && handle < OS_lenght){
        __OSOperation[handle].isOpen = 0;
    }
    return -1;
}
