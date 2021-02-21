#include "gpio.h"

void gpio_init(void)
{
	 SYSCTL->RCGCGPIO |= 0x05;
	 GPIOF->DEN |= 0x0E;
	 GPIOF->DIR |= 0x0E;
}

void gpio_toggle(void)
{
	GPIOF->DATA ^= 0x02;
}
