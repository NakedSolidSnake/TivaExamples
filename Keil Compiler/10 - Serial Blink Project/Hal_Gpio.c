#include "Hal_Gpio.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

static GPIOA_Type *Gpio_Get_Dev(GPIO_Dev dev)
{
	GPIOA_Type *gpio;
	switch(dev)
	{
		case GPIO_DEV_A:
			gpio = (GPIOA_Type *)GPIOA_BASE;
			break;
		
		case GPIO_DEV_B:
			gpio = (GPIOA_Type *)GPIOB_BASE;
		  break;
		
		case GPIO_DEV_C:
			gpio = (GPIOA_Type *)GPIOC_BASE;
		  break;
		
		case GPIO_DEV_D:
			gpio = (GPIOA_Type *)GPIOD_BASE;
		  break;
			
		case GPIO_DEV_E:
			gpio = (GPIOA_Type *)GPIOE_BASE;
		  break;
		
		case GPIO_DEV_F:
			gpio = (GPIOA_Type *)GPIOF_BASE;
		  break;
	}	
	return gpio;
}

static void Gpio_Enable_Clock(GPIO_Dev dev)
{
	SYSCTL->RCGCGPIO |= SHIFT(dev);
}

static void Gpio_Disable_Clock(GPIO_Dev dev)
{
	SYSCTL->RCGCGPIO &= ~SHIFT(dev);
}

static void Gpio_Set_Direction(GPIOA_Type * gpio, uint32_t pin, GPIO_Direction direction)
{
	if(direction == GPIO_OUTPUT)
		gpio->DIR |= SHIFT(pin);
	else
		gpio->DIR &= ~SHIFT(pin);
}

static void Gpio_Set_Strength(GPIOA_Type * gpio,  uint32_t pin, GPIO_Strength strength)
{
	if(strength == GPIO_2MA)
		gpio->DR2R |= SHIFT(pin);
	else if(strength == GPIO_4MA)
		gpio->DR4R |= SHIFT(pin);
	else 
		gpio->DR8R |= SHIFT(pin);
}

static void Gpio_Set_PullUp(GPIOA_Type * gpio,  uint32_t pin, GPIO_PullMode pull_mode)
{
	if(pull_mode == GPIO_PULLDOWN)
		gpio->PDR |= SHIFT(pin);
	else
		gpio->PUR |= SHIFT(pin);
}

static void Gpio_Enable_Digital(GPIOA_Type * gpio, uint32_t pin)
{
	gpio->DEN |= SHIFT(pin);
}

static void Gpio_Clear_Interruption(GPIOA_Type * gpio, uint32_t pin)
{
	volatile uint32_t dev;
	dev = SHIFT(pin);
	gpio->ICR = SHIFT(pin);	
}

static void Gpio_Enable_Interruption(GPIOA_Type * gpio, uint32_t pin)
{
	gpio->IS &= ~SHIFT(pin);
	gpio->IBE &= ~SHIFT(pin);
	gpio->IEV |= SHIFT(pin);
	Gpio_Clear_Interruption(gpio, pin);
	gpio->IM |= SHIFT(pin);
	__NVIC_EnableIRQ(GPIOF_IRQn);	
//	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
//  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
//	EnableInterrupts();
}

static void Gpio_Disable_Interruption(GPIOA_Type * gpio, uint32_t pin)
{
	
}


uint32_t Hal_Gpio_Init(Hal_Gpio_Config_t *config)
{
	//instructions about initialization on pg 656
	uint32_t ret;
	GPIOA_Type *gpio;
	
	//get device
	gpio = Gpio_Get_Dev(config->dev);	
	//enable clock
	Gpio_Enable_Clock(config->dev);	
	//enable direction	
	Gpio_Set_Direction(gpio, config->pin, config->direction); 

   gpio->AFSEL &= ~SHIFT(config->pin);
	//enable digital
	Gpio_Enable_Digital(gpio, config->pin);
	gpio->PCTL &= ~0x000F0000;
	gpio->AMSEL &= ~SHIFT(config->pin);
	
	
	if(config->direction == GPIO_OUTPUT){
			//configure strength -- output
		Gpio_Set_Strength(gpio, config->pin, config->strength);
	}
	else{
		//configure pullup -- input
		Gpio_Set_PullUp(gpio, config->pin, config->pullmode);	
	}
		//configure alternate pin	
	
	
	//enable interruption
	if(config->interrupt == GPIO_INT_ON)
		Gpio_Enable_Interruption(gpio, config->pin);
	return 0;
}

uint32_t Hal_Gpio_Write(GPIO_Dev dev, uint32_t pin, GPIO_State level_state)
{
	GPIOA_Type *gpio;	
	gpio = Gpio_Get_Dev(dev);
	
	if(level_state == GPIO_LOW)
		gpio->DATA |= SHIFT(pin);
	else
		gpio->DATA &= ~SHIFT(pin);
	
}

uint8_t Hal_Gpio_Read(GPIO_Dev dev, uint32_t pin)
{
	GPIOA_Type *gpio;	
	gpio = Gpio_Get_Dev(dev);
	uint8_t readPin = gpio->DATA;
	readPin = (readPin & SHIFT(pin)) != SHIFT(pin);	
	return readPin;
}

uint8_t Hal_Gpio_Ioctl(GPIO_Dev dev, COMMAND command, uint32_t pin)
{
	GPIOA_Type *gpio;	
	gpio = Gpio_Get_Dev(dev);
	
	switch(command)
	{
		case GPIO_CLEAR_INT:
			Gpio_Clear_Interruption(gpio, pin);
			break;
	  case GPIO_SET_INT:
			break;
	}
}