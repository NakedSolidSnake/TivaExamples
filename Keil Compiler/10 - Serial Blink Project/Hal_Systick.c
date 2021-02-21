#include "Hal_Systick.h"

#define SYSTICK_ENABLE_PIN    0

#define SYSTICK_COUNT_OFFSET 16
#define SYSTICK_INT_OFFSET    1

#define SYSTICK_LOAD_MASK 0x00FFFFFF

static void Systick_Enable(void){
	SysTick->CTRL |= SHIFT(SYSTICK_ENABLE_PIN);
}

static void Systick_Disable(void){
	SysTick->CTRL &= ~SHIFT(SYSTICK_ENABLE_PIN);
}

static void Systick_Int_Enable(void){
	SysTick->CTRL |= SHIFT(SYSTICK_INT_OFFSET);
}

static void Systick_Int_Disable(void){
	SysTick->CTRL &= ~SHIFT(SYSTICK_INT_OFFSET);
}

uint32_t Hal_Systick_Init(Hal_Systick_Config_t *systick)
{
	SysTick->CTRL = 0;
	SysTick->CTRL |= SHIFT(2);
	Hal_Systick_Set_Load(systick->loadValue);
	Systick_Int_Enable();
	Systick_Enable();
}

uint32_t Hal_Systick_Set_Load(uint32_t value)
{
	SysTick->LOAD = (value & SYSTICK_LOAD_MASK);
}

uint32_t Hal_Systick_GetTick(void)
{
	return SysTick->VAL & SYSTICK_LOAD_MASK;
}

uint8_t Hal_Systick_Count_Over(void)
{
	uint8_t ret = SysTick->CTRL;
	return (ret & SHIFT(SYSTICK_COUNT_OFFSET));
}