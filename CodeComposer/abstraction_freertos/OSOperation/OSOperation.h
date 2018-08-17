/*
 * OSOperation.h
 *
 *  Created on: 2 de dez de 2017
 *      Author: solid
 */

#ifndef OSOPERATION_H_
#define OSOPERATION_H_


typedef struct _OSOperation{
    char *name;
    unsigned char isOpen;
    short (*open)(void);
    short (*read)(char *buf, unsigned int length);
    short (*write)(char *buf, unsigned int length);
    short (*ioctl)(unsigned int action, void *parameter);
    short (*close)(void);
}OSOperation;




short dev_open(const char *dev);

short dev_read(short handle, char *buf, unsigned int lenght);

short dev_write(short handle, char *buf, unsigned int lenght);

short dev_ioctl(short handle, unsigned int option, void *parameter);

short dev_close(short handle);

#endif /* OSOPERATION_H_ */
