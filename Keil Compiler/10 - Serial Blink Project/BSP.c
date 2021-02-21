#include "BSP.h"
#include <stdlib.h>

#define SHIFT(x) ( 1 << (x))

uint32_t System_Init(SYSCTL_Type * dev)
{
	uint32_t devs = 0;
	
	return devs;
}

void Systick_Init(void)
{
	
}

uint32_t Systick_TickGet(void)
{
	uint32_t value = 0;
	
	return value;
}


void GPIO_Init(GPIOA_Type *gpio)
{
	gpio = (GPIOA_Type *)GPIOF_BASE;
	SYSCTL->RCGCGPIO |= SHIFT(5);
	gpio->LOCK = 0x4C4F434B;
	gpio->CR = 0x01;
	gpio->DIR &= ~0x11;	
	gpio->DIR |= 0x0E;	
	gpio->DEN |= 0x1F;
	gpio->PUR |= 0x11;
	
}

void GPIO_Set(GPIOA_Type *gpio, uint8_t pins)
{
	gpio = (GPIOA_Type *)GPIOF_BASE;
	gpio->DATA |= SHIFT(pins);
}

void GPIO_Toggle(GPIOA_Type *gpio, uint8_t pins)
{
	gpio = (GPIOA_Type *)GPIOF_BASE;
	gpio->DATA ^= SHIFT(pins);
}

void GPIO_Clear(GPIOA_Type *gpio, uint8_t pins)
{
	gpio = (GPIOA_Type *)GPIOF_BASE;
	gpio->DATA &= ~SHIFT(pins);
}

uint8_t GPIO_Read(GPIOA_Type *gpio)
{
	uint8_t kbd;
	gpio = (GPIOA_Type *)GPIOF_BASE;
	
	kbd = gpio->DATA;
	
	return kbd;
}


static void Send_Char(UART0_Type *uart, const char msg)
{
	while((uart->FR & 0x20) != 0){}
      uart->DR = msg;
}

static uint8_t Get_Char(UART0_Type *uart)
{
	uint8_t read = 0;
	if((uart->FR & 0x10) != 0){}
  read = uart->DR & 0xFF;
	if(read != 0)
		return read;
	return 0;
}

void UART_init(UART0_Type *uart, uint32_t baudRate)
{
	uint32_t bus_clock = 16000000U;
	float value = 0;
  uint32_t complet_part = 0;
	uint32_t baud = baudRate;
	
	GPIOA_Type *gpio = (GPIOA_Type *)GPIOA_BASE;		
	uart = (UART0_Type *) UART0_BASE;
	
	SYSCTL->RCGCUART |= SHIFT(0);
	SYSCTL->RCGCGPIO |= SHIFT(0);
	
	uart->CTL &= ~SHIFT(0);
	
//	value = (float)bus_clock/(16 * baud);
//  complet_part = value;
//  value = value - complet_part;
//  value = value*64.0 + 0.5;
//  _uart->IBRD = complet_part;
//  _uart->FBRD = (uint32_t)value;	
	uart->IBRD = 27;
  uart->FBRD = 8;
	uart->CC = 0;
	uart->LCRH = 0x60;  //set bits Mode
	uart->CTL |= 1;
	
//	gpio->AFSEL |= SHIFT(0) | SHIFT(1);
//	gpio->DEN |= SHIFT(0) | SHIFT(1);
  gpio->AFSEL |= 0x03;
	gpio->DEN |= 0x03;
	gpio->PCTL  &= ~0x000000FF;
	gpio->PCTL  |= 0x00000011;
	gpio->AMSEL &= ~0x03;	
}

void UART_Send(UART0_Type *uart, const uint8_t *message, uint32_t size)
{
	 while(*message){
        Send_Char(uart, *message);
        message++;
    }	
}

uint32_t UART_Read(UART0_Type *uart, uint8_t *message, uint32_t *size)
{
	uint32_t read = 0;
	uint32_t index = 0;
	if(message == NULL)
		return 1;
	while(((*size--) != 0))
	{
		message[index] = Get_Char(uart);
	}

	return read;
}

void PLL_Init(void){
  
  SYSCTL->RCC2 |= 0x80000000;  
  SYSCTL->RCC2 |= 0x800;
  
  SYSCTL->RCC &= ~0x7C0;   
  SYSCTL->RCC += 0x540;    
  SYSCTL->RCC &= ~0x70;
  SYSCTL->RCC += 0x00;
  
  SYSCTL->RCC2 &= ~0x2000;
  
  SYSCTL->RCC2 |= 0x40000000;  
  SYSCTL->RCC2 = (SYSCTL->RCC2 &~0x1FC00000) + (7 <<22);  
  
  while((SYSCTL->RIS & 0x40)==0){};
  
  SYSCTL->RCC2  &= ~0x800;
}
