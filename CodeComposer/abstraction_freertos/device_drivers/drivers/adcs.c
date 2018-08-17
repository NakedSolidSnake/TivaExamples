/*
 * adcs.c
 *
 *  Created on: 9 de dez de 2017
 *      Author: solid
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "utils/uartstdio.h"
#include "driverlib/sysctl.h"
#include "modules/hal_uart.h"
#include "driverlib/timer.h"
#include "adcs.h"

void ADC_init_low_level(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlDelay(3);
    //
    // Wait for the ADC0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
    {}
    //
    // Enable the first sample sequencer to capture the value of channel 0 when
    // the processor trigger occurs.
    //
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0,
                             ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
    ADCSequenceEnable(ADC0_BASE, 3);
    //

    // Wait until the sample sequence has completed.
    ADCIntClear(ADC0_BASE, 3);
}


void adc_read_value(uint32_t *ui32Value){

    /* As per most tasks, this task is implemented in an infinite loop. */
    /* Print out the name of this task. */
    ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false)){

    }
    ADCSequenceDataGet(ADC0_BASE, 3, ui32Value);
    ADCIntClear(ADC0_BASE, 3);
}

