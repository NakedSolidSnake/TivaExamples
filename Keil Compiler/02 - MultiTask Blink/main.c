#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"  

#include "TM4C123.h"                    // Device header

#define LED_RED   0x02
#define LED_GREEN 0x04
#define LED_BLUE  0x08

void InitLed(void)
{
	SYSCTL->RCGCGPIO |= (1 << 5);
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
}

void toogleLedRed(void)
{	 
	 GPIOF->DATA ^= LED_RED ; 	 
}

void toogleLedGreen(void)
{	 
	 GPIOF->DATA ^= LED_GREEN ; 	 
}

void toogleLedBlue(void)
{	 
	 GPIOF->DATA ^= LED_BLUE ; 	 
}

void taskLedRed(void *pvParameter)
{
	(void)pvParameter;
                     // ARM.FreeRTOS::RTOS:Core
	uint32_t xDelay100ms = pdMS_TO_TICKS( 100 );
   
   while(1)		 
	 {	
		  toogleLedRed();
		  vTaskDelay(xDelay100ms);
	 }
	
}


void taskLedGreen(void *pvParameter)
{
	(void)pvParameter;
                     // ARM.FreeRTOS::RTOS:Core
	uint32_t xDelay250ms = pdMS_TO_TICKS( 250 );
   
   while(1)		 
	 {	
		  toogleLedGreen();
		  vTaskDelay(xDelay250ms);
	 }
	
}


void taskLedBlue(void *pvParameter)
{
	(void)pvParameter;
                     // ARM.FreeRTOS::RTOS:Core
	uint32_t xDelay750ms = pdMS_TO_TICKS( 750 );
   
   while(1)		 
	 {	
		  toogleLedBlue();
		  vTaskDelay(xDelay750ms);
	 }
	
}



int main()	
{
	BaseType_t bRet = 0;
	InitLed();	
	bRet = xTaskCreate(taskLedRed, "task Red", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	bRet = xTaskCreate(taskLedGreen, "task Green", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	bRet = xTaskCreate(taskLedBlue, "task Blue", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	if(bRet != pdTRUE)
		goto error;
	vTaskStartScheduler();
error:
	while(1);		
}
