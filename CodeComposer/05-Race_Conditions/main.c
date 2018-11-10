#include "TM4C123GH6PM.h"
#include "bsp.h"


//prevent race condition    -- state = 0 clear bit, --state = 1 set bit
void setLed(uint8_t leds, uint8_t state)
{
    __disable_irq();

    if(state)
    {
        GPIOF_AHB->DATA |= leds;
    }
    else
    {
        GPIOF_AHB->DATA &= ~leds;
    }
    __enable_irq();
}

int main() {
    SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    SysTick->LOAD = SYS_CLOCK_HZ - 1U;
    SysTick->VAL  = 0U;
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U;

    SysTick_Handler();

    __enable_irq();
    while (1) {
    //    GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
    //    GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;

        setLed(LED_GREEN, 1);
        setLed(LED_GREEN, 0);
    }
    //return 0;
}
