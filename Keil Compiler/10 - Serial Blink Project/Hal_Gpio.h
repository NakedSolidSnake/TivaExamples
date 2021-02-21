#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#include "Common.h"

typedef enum COMMAND{
	GPIO_CLEAR_INT,
	GPIO_SET_INT,
}COMMAND;

typedef void (*GPIO_Handler)(void);

typedef enum GPIO_Dev{
	GPIO_DEV_A,
	GPIO_DEV_B,
	GPIO_DEV_C,
	GPIO_DEV_D,
	GPIO_DEV_E,
	GPIO_DEV_F
}GPIO_Dev;

typedef enum GPIO_Direction{
	GPIO_OUTPUT,
	GPIO_INPUT
}GPIO_Direction;

typedef enum GPIO_Strength{
	GPIO_2MA,
	GPIO_4MA,
	GPIO_8MA
}GPIO_Strength;

typedef enum GPIO_State{
	GPIO_LOW,
	GPIO_HIGH	
}GPIO_State;

typedef enum GPIO_PullMode{
	GPIO_PULLUP,
	GPIO_PULLDOWN
}GPIO_PullMode;

typedef enum GPIO_InterruptControl
{
	GPIO_INT_OFF, 
	GPIO_INT_ON
}GPIO_InterruptControl;

typedef struct Hal_Gpio_Config{
	GPIO_Dev dev;
	uint32_t pin;
	GPIO_Direction direction;
	GPIO_Strength strength;
	GPIO_PullMode pullmode;
	GPIO_State inital_state;
	GPIO_InterruptControl interrupt;
	GPIO_Handler handler;	
}Hal_Gpio_Config_t;



/**

*/
uint32_t Hal_Gpio_Init(Hal_Gpio_Config_t *config);

/**

*/

uint32_t Hal_Gpio_Write(GPIO_Dev dev, uint32_t pin, GPIO_State level_state);

/**

*/
uint8_t Hal_Gpio_Read(GPIO_Dev dev, uint32_t pin);

/**

*/
uint8_t Hal_Gpio_Ioctl(GPIO_Dev dev, COMMAND command, uint32_t pin);

#endif /* _HAL_GPIO_H */

