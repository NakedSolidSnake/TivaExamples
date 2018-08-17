/*
 * filter.h
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */

#ifndef FILTER_FILTER_H_
#define FILTER_FILTER_H_

#include <stdint.h>

typedef enum _FILTER_TYPE{
    PID,
    IIR,
    FIR
}FILTER_TYPE;

typedef struct _FILTER{
    FILTER_TYPE filter;
    float error;
    float integral;
    float derivative;
    float proportional;
    float kp;
    float ki;
    float kd;
    float ideal;
}FILTER;

uint32_t TempCelsiusGrad(uint32_t temp);
void filter_set(FILTER *filter);
uint32_t PID_filter(uint32_t value);

#endif /* FILTER_FILTER_H_ */
