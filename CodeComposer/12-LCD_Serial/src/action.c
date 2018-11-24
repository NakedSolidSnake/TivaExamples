/*
 * action.c
 *
 *  Created on: 24 de nov de 2018
 *      Author: solid
 */


#include <action.h>
#include <stdbool.h>
#include <string.h>

#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"


#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"

#define LED_RED         GPIO_PIN_1
#define LED_BLUE        GPIO_PIN_2
#define LED_GREEN       GPIO_PIN_3


static void LED_RED_ON(void);
static void LED_RED_OFF(void);
static void LED_BLUE_ON(void);
static void LED_BLUE_OFF(void);
static void LED_GREEN_ON(void);
static void LED_GREEN_OFF(void);

const uint8_t *menu_items[] = {
                               "RED ON",
                               "RED OFF",
                               "GREEN ON",
                               "GREEN OFF",
                               "BLUE ON",
                               "BLUE OFF",
};

const uint8_t menu_items_amount = sizeof(menu_items)/ sizeof(menu_items[0]);


typedef void (*action)(void);

static const action actions[] = {
       LED_RED_ON,
       LED_RED_OFF,
       LED_GREEN_ON,
       LED_GREEN_OFF,
       LED_BLUE_ON,
       LED_BLUE_OFF,
};

const uint8_t actions_amount = sizeof(actions)/sizeof(actions[0]);

void LEDS_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED  | LED_BLUE | LED_GREEN);
}

static void LED_RED_ON(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_RED  , LED_RED);
}

static void LED_RED_OFF(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE,   LED_RED , 0);
}

static void LED_BLUE_ON(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE,  LED_BLUE , LED_BLUE);
}

static void LED_BLUE_OFF(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE,  LED_BLUE , 0);
}

static void LED_GREEN_ON(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, LED_GREEN);
}

static void LED_GREEN_OFF(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, LED_GREEN, 0);
}

uint8_t Action_Select(const uint8_t * option)
{
    int i;
    if(option == (void *)0)
    {
        return 0;
    }

    for( i = 0; i < actions_amount; i++)
    {
        if(!strcmp(option, menu_items[i]))
        {
            actions[i]();
            return 0;
        }
    }
    return 1;
}

