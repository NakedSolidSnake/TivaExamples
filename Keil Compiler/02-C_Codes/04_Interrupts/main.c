#include "TM4C123.h"                    // Device header
#include <stdint.h>

#define LED_RED  		(1U << 1)
#define LED_BLUE 		(1U << 2)
#define LED_GREEN 	(1U << 3)

void delay(int volatile time);

void SysTick_Handler(void)
{
	GPIOF_AHB->DATA ^= LED_BLUE;
}

void inc(void)
{
	volatile int a = 10;
	a += 1;
}
	

int main()
{
	SYSCTL->RCGC2 |= (1 << 5);	/* Enable clock port F*/
	SYSCTL->GPIOHBCTL |= (1 << 5);
	GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
	GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
	
	inc();
	
	SysTick->CTRL = 0; 
	SysTick->LOAD = SystemCoreClock / 2U - 1U;
	SysTick->VAL = 0U;
	SysTick->CTRL = (1U << 2) | (1U << 1) | (1U << 0);
	
	GPIOF_AHB->DATA |= LED_BLUE;
	
	__enable_irq();
	
	while(1)
	{
		//put code here
		GPIOF_AHB->DATA ^= LED_RED;
		delay(5000000);		
	}
}

void delay(int volatile time)
{
	while(time > 0){
		--time;
	}
}
