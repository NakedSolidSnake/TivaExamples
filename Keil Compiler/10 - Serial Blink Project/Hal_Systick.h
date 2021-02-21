#ifndef _HAL_SERIAL_H
#define _HAL_SERIAL_H

#include "Common.h"

typedef void (*Systick_Handler)(void);

typedef struct Hal_Systick_Config{
	uint32_t loadValue;
	Systick_Handler handler;
}Hal_Systick_Config_t;

uint32_t Hal_Systick_Init(Hal_Systick_Config_t *systick);

uint32_t Hal_Systick_Set_Load(uint32_t value);

uint32_t Hal_Systick_GetTick(void);

uint8_t Hal_Systick_Count_Over(void);

#endif /* _HAL_SERIAL_H */