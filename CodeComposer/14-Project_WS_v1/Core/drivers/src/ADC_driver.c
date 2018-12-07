/*
 * ADC.c
 *
 *  Created on: 25 de nov de 2018
 *      Author: solid
 */

#include <ADC_driver.h>
#include <stdbool.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_types.h"

#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"

uint8_t ADC_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlDelay(3);

    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_TS | ADC_CTL_IE | ADC_CTL_END);


    ADCSequenceEnable(ADC0_BASE, 3);

    ADCIntClear(ADC0_BASE, 3);

    return 0;
}

uint32_t ADC_Read(void)
{
    uint32_t read_value = 0;
    ADCProcessorTrigger(ADC0_BASE, 3);


    while(!ADCIntStatus(ADC0_BASE, 3, false))
    {
    }

    ADCIntClear(ADC0_BASE, 3);

    ADCSequenceDataGet(ADC0_BASE, 3, &read_value);

    return read_value;
}



