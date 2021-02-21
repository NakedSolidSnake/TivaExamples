#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"  

#include "TM4C123.h"                    // Device header


void InitLed(void)
{
	SYSCTL->RCGCGPIO |= (1 << 5);
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
}

void toogleLed(void)
{	 
	 GPIOF->DATA ^= 0x02 ; 	 
}


void task(void *pvParameter)
{
	(void)pvParameter;
                     // ARM.FreeRTOS::RTOS:Core
	uint32_t xDelay500ms = pdMS_TO_TICKS( 500 );
   
   while(1)		 
	 {	
		  toogleLed();
		  vTaskDelay(xDelay500ms);
	 }
	
}


int main()	
{
	BaseType_t bRet = 0;
	InitLed();	
	toogleLed();
	toogleLed();
	bRet = xTaskCreate(&task, "task name", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	if(bRet != pdTRUE)
		goto error;
	vTaskStartScheduler();
error:
	while(1);		
}
