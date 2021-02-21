#ifndef _BSP_H
#define _BSP_H

#include "TM4C123.h"                    // Device header
#include <stdint.h>

uint32_t System_Init(SYSCTL_Type * dev);
void Systick_Init(void);
uint32_t Systick_TickGet(void);
void GPIO_Init(GPIOA_Type *gpio);
void GPIO_Set(GPIOA_Type *gpio, uint8_t pins);
void GPIO_Toggle(GPIOA_Type *gpio, uint8_t pins);
void GPIO_Clear(GPIOA_Type *gpio, uint8_t pins);
uint8_t GPIO_Read(GPIOA_Type *gpio);
void UART_init(UART0_Type *uart, uint32_t baudRate);
void UART_Send(UART0_Type *uart, const uint8_t *message, uint32_t size);
uint32_t UART_Read(UART0_Type *uart, uint8_t *message, uint32_t *size);

void PLL_Init(void);

#endif

