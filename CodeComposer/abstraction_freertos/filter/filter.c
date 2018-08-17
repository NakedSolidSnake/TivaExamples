/*
 * filter.c
 *
 *  Created on: 10 de dez de 2017
 *      Author: solid
 */


#include <stdint.h>
#include "filter.h"

uint32_t TempCelsiusGrad(uint32_t temp){
    return (uint32_t)(147.5 - ((75.0*3.3 *(float)temp)) / 4096.0);
}

static FILTER filter = {
                        .filter = PID,
                        .error = 0.0,
                        .integral = 0.0,
                        .proportional = 0.0,
                        .derivative = 0.0,
                        .kp = 1.0,
                        .ki = 0.0,
                        .kd = 0.0,
                        .ideal = 25.0
};


uint32_t PID_filter(uint32_t value){
    static uint32_t lastValue = 0;
    filter.error = filter.ideal - value;
    filter.proportional = filter.error * filter.kp;
    filter.integral += filter.error *filter.ki;
    filter.derivative = (lastValue - value) * filter.kd;
    lastValue = value;
    return (filter.proportional + filter.integral + filter.derivative);
}

void filter_set(FILTER *_filter){
    _filter->filter = PID;
    _filter->error = 0.0;
    _filter->integral = 0.0;
    _filter->proportional = 0.0;
    _filter->derivative = 0.0;
    _filter->kp = 1.0;
    _filter->ki = 0.0;
    _filter->kd = 0.0;
    _filter->ideal = 25.0;
}
/**/
