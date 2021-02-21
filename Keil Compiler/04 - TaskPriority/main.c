#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"  

#include "TM4C123.h"                    // Device header

#define LED_RED   0x02
#define LED_BLUE  0x08

struct LedCtx{
	const uint32_t led;
	const TickType_t delay; 
};

struct LedCtx ledRed = {
		.led = LED_RED,
		.delay = 100
	};
	
	struct LedCtx ledBlue = {
		.led = LED_BLUE,
		.delay = 100
	};	


void InitLed(void)
{
	SYSCTL->RCGCGPIO |= (1 << 5);
	GPIOF->DIR |= 0x0E;
	GPIOF->DEN |= 0x0E;
}

void toogleLed(uint32_t led)
{	
  long int i;	
	
	GPIOF->DATA ^= led ; 	 	
	for(i = 0; i < 7000000; i++);
	
	GPIOF->DATA ^= led ; 	 	
	for(i = 0; i < 7000000; i++);
}


void taskToggle(void *pvParameter)
{
	 volatile struct LedCtx *led = (struct LedCtx *)pvParameter;
                     
	 TickType_t delay = pdMS_TO_TICKS( led->delay );
   long int i;
   while(1)		 
	 {	
		  toogleLed(led->led);		 
		  //vTaskDelay(delay);
	 }
	
}

int main()	
{
	BaseType_t bRet = 0;
	InitLed();
	
	
	bRet = xTaskCreate(taskToggle, "task Red"  , configMINIMAL_STACK_SIZE  , (void *)&ledRed  , 2, NULL);	
	bRet = xTaskCreate(taskToggle, "task Blue" , configMINIMAL_STACK_SIZE , (void *)&ledBlue , 1, NULL);
	if(bRet != pdTRUE)
		goto error;
	vTaskStartScheduler();
error:
	while(1);		
}
