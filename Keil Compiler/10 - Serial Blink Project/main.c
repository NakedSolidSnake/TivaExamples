#include "BSP.h"

#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "queue.h"
#include "Hal_Gpio.h"
#include "Hal_Systick.h"
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core


#include <stdlib.h>
#include <stdio.h>
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers



#define LED_RED   1
#define LED_BLUE  2
#define LED_GREEN 3

#define LED_GREEN_EVENT (1 << 0)
#define EVENT_2 (1 << 1)
#define EVENT_3 (1 << 2)

#define SW_4      4


QueueHandle_t xQueue;
EventGroupHandle_t xEventGroup; 
SemaphoreHandle_t xSemaphore ;
TaskHandle_t tLedRed, tLedBlue, tLedGreen, tMessage, tButton;


void printMessage(const char * msg);

void printMessage(const char * msg)
{
	UART0_Type *uart = (UART0_Type *)UART0_BASE;
	
	if(xSemaphoreTake( xSemaphore, ( TickType_t ) 10 ) == pdTRUE)
	{
		UART_Send(uart, (const uint8_t *)msg, strlen(msg));
		xSemaphoreGive( xSemaphore );
	}
}

 
  
 Hal_Gpio_Config_t ledRed = {
		.dev = GPIO_DEV_F,		
	  .pin = LED_RED,
	  .direction = 	GPIO_OUTPUT,
	  .pullmode = 0,
	  .inital_state = GPIO_LOW,
	  .interrupt = GPIO_INT_OFF,
	  .handler = NULL	
	};
 
	Hal_Gpio_Config_t ledBlue = {
		.dev = GPIO_DEV_F,		
	  .pin = LED_BLUE,
	  .direction = 	GPIO_OUTPUT,
	  .pullmode = 0,
	  .inital_state = GPIO_LOW,
	  .interrupt = GPIO_INT_OFF,
	  .handler = NULL	
	};
	
	Hal_Gpio_Config_t ledGreen = {
		.dev = GPIO_DEV_F,		
	  .pin = LED_GREEN,
	  .direction = 	GPIO_OUTPUT,
	  .pullmode = 0,
	  .inital_state = GPIO_LOW,
	  .interrupt = GPIO_INT_OFF,
	  .handler = NULL	
	};
	
	Hal_Gpio_Config_t bt4 = {
		.dev = GPIO_DEV_F,		
	  .pin = SW_4,
	  .direction = 	GPIO_INPUT,
	  .pullmode = GPIO_PULLUP,
    .interrupt = GPIO_INT_OFF,	  
	  .handler = NULL	
	};
 

//void vTask_Serial_Read(void *pvParameters)
//{	
	//TickType_t _100_ms = pdMS_TO_TICKS(100);
//	UART0_Type *uart = (UART0_Type *)UART0_BASE;
//	uint32_t s = 1;
//	uint8_t msg;
//	const char *messsge = "OK\n";
//	while(1)
//	{		
//		UART_Read(uart, &msg, &s);
//		if(msg != 0){
//			UART_Send(uart, (const uint8_t *)messsge, strlen(messsge));
//			msg = 0;
//		}
//		//vTaskDelay(_100_ms);
//	}
//}


/**********************************************************************************/
/*             Tasks  Implementation Start                                        */
/**********************************************************************************/
void vTask_Led_Red(void *pvParameters)
{	
	TickType_t xDelay_250ms = pdMS_TO_TICKS((TickType_t)250);
	GPIOA_Type *gpio = (GPIOA_Type *)GPIOF_BASE;
	
	while(1)
	{
		//blink led here
		GPIO_Toggle(gpio, LED_RED); 
		vTaskDelay(xDelay_250ms);
	}
}

void vTask_Led_Green(void *pvParameters)
{
	TickType_t xDelay_500ms = pdMS_TO_TICKS((TickType_t)500);
	GPIOA_Type *gpio = (GPIOA_Type *)GPIOF_BASE;
	
	EventBits_t xEventGroupValue;
	const EventBits_t xBitsToWaitFor = LED_GREEN_EVENT;
	
	while(1)
	{
		xEventGroupValue = xEventGroupWaitBits( xEventGroup,
																						xBitsToWaitFor,
																						pdTRUE,
																						pdFALSE,
																						portMAX_DELAY);
		if((xEventGroupValue & LED_GREEN_EVENT) != 0)
			GPIO_Toggle(gpio, LED_GREEN); 
		vTaskDelay(xDelay_500ms);
	}
}

void vTask_Led_Blue(void *pvParameters)
{
	TickType_t xDelay_100ms = pdMS_TO_TICKS((TickType_t)100);
	GPIOA_Type *gpio = (GPIOA_Type *)GPIOF_BASE;
	uint8_t recv = 0;
	while(1)
	{
		if( xQueueReceive( xQueue, &( recv ), ( TickType_t ) 0 ) )
			GPIO_Toggle(gpio, LED_BLUE); 
		vTaskDelay(xDelay_100ms);
	}
}

void vTask_Button(void *pvParameters)
{	
	uint8_t readKey;
	TickType_t _100_ms = pdMS_TO_TICKS(100);
	while(1)
	{
		readKey = GPIO_Read((GPIOA_Type *)GPIOF_BASE);
		if( (readKey & 0x11) != 0x11 )
		{			
			xQueueSend( xQueue, ( void * ) &readKey, ( TickType_t ) 10 );
		}
		vTaskDelay(_100_ms);
	}
}

void vTask_SendMessage(void *pvParameters)
{	
	uint8_t readKey;
	TickType_t xDelay_1000_ms = pdMS_TO_TICKS(1000);
	while(1)
	{
		
		printMessage("This is a message\n");
		vTaskDelay(xDelay_1000_ms);
	}
}

/**********************************************************************************/
/*             Tasks  Implementation END                                          */
/**********************************************************************************/

/*================================================================================*/

/**********************************************************************************/
/*             Callbacks Implementation START                                     */
/**********************************************************************************/
void vTimerCallback( TimerHandle_t xTimer )
{
	xEventGroupSetBits(xEventGroup, LED_GREEN_EVENT);
}

void vTimerCallbackCheckTasks( TimerHandle_t xTimer )
{
	char buffer[100] = {0};
	UBaseType_t uxHighWaterMark[5] = {0};	
	uxHighWaterMark[0] =  uxTaskGetStackHighWaterMark(tLedRed);
	uxHighWaterMark[1] =  uxTaskGetStackHighWaterMark(tLedBlue);
	uxHighWaterMark[2] =  uxTaskGetStackHighWaterMark(tLedGreen);
	uxHighWaterMark[3] =  uxTaskGetStackHighWaterMark(tButton);
	uxHighWaterMark[4] =  uxTaskGetStackHighWaterMark(tMessage);
	
	sprintf(buffer, "Red = %d\nBlue = %d\nGreen = %d\nButton = %d\nMessage = %d\n", uxHighWaterMark[0], uxHighWaterMark[1], uxHighWaterMark[2], uxHighWaterMark[3], uxHighWaterMark[4]);
	
	printMessage(buffer);
}


/**********************************************************************************/
/*             Callbacks Implementation END                                     */
/**********************************************************************************/
	



int main()
{
//	PLL_Init();	
	
 	Hal_Gpio_Init(&ledRed);
	Hal_Gpio_Init(&ledBlue);
	Hal_Gpio_Init(&ledGreen);
	Hal_Gpio_Init(&bt4);	
	
	UART0_Type *uart = (UART0_Type *)UART0_BASE;
	GPIO_Init(NULL);
	UART_init(uart, 115200);
		
	xQueue = xQueueCreate(1, sizeof(uint8_t));
	if(xQueue == 0)
	{
		for(;;);
	}
	
	xEventGroup = xEventGroupCreate();
	if(xEventGroup == 0)
	{
			for(;;);
	}	
	
	xSemaphore = xSemaphoreCreateMutex();
	if(xSemaphore == 0)
	{
			for(;;);
	}
	
//	xTaskCreate(vTask_Button, "Task_Button", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//	xTaskCreate(vTask_Led,    "Task_Led"   , configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	//xTaskCreate(vTask_Serial_Write, "Task_Serial", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//	xTaskCreate(vTask_Serial_Print, "Task_Serial", configMINIMAL_STACK_SIZE, "Message task 1 sending...\n", 1, NULL);
//	xTaskCreate(vTask_Serial_Print, "Task_Serial", configMINIMAL_STACK_SIZE, "Message task 2 sending...\n", 1, NULL);
//	xTaskCreate(vTask_Serial_PrintEvent, "Task_Serial", configMINIMAL_STACK_SIZE, "Message task 3 sending...\n", 2, NULL);
	//xTaskCreate(vTask_Serial_Read, "Task_Serial", configMINIMAL_STACK_SIZE * 3, NULL, 1, NULL);		
	//xTaskCreate(vTask_SetEvent, "Task_Serial", configMINIMAL_STACK_SIZE * 3, NULL, 1, NULL);	
//	xTaskCreate(vTask_Serial_PrintEvent, "Task_Serial", configMINIMAL_STACK_SIZE * 5, NULL, 2, NULL);	

		xTaskCreate(vTask_Led_Red     , "Task_Led_Red"   , configMINIMAL_STACK_SIZE, NULL, 1, tLedRed);
	  xTaskCreate(vTask_Led_Blue    , "Task_Led_Blue"  , configMINIMAL_STACK_SIZE, NULL, 1, tLedBlue);
	  xTaskCreate(vTask_Led_Green   , "Task_Led_Green" , configMINIMAL_STACK_SIZE, NULL, 1, tLedGreen);
	  xTaskCreate(vTask_Button      , "Task_Button"    , configMINIMAL_STACK_SIZE, NULL, 1, tButton);
	  xTaskCreate(vTask_SendMessage , "Task_Message"   , configMINIMAL_STACK_SIZE, NULL, 1, tMessage);
	
//	  xTaskCreate(vTask_Led_Red     , "Task_Led_Red"   , configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//	  xTaskCreate(vTask_Led_Blue    , "Task_Led_Blue"  , configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//	  xTaskCreate(vTask_Led_Green   , "Task_Led_Green" , configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//	  xTaskCreate(vTask_Button      , "Task_Button"    , configMINIMAL_STACK_SIZE, NULL, 1, NULL);
//	  xTaskCreate(vTask_SendMessage , "Task_Message"   , configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	
	  //create timer
	  TimerHandle_t timer = xTimerCreate("Timer Set Event", pdMS_TO_TICKS(1000), pdTRUE, ( void * ) 0, vTimerCallback);	  		
		TimerHandle_t timerHealth = xTimerCreate("Timer Check Health", pdMS_TO_TICKS(5000), pdTRUE, ( void * ) 0, vTimerCallbackCheckTasks);
	
		if(xTimerStart(timer, 0) != pdPASS)
			for(;;);
		
		if(xTimerStart(timerHealth, 0) != pdPASS)
			for(;;);
	
	vTaskStartScheduler();
	for(;;);	
}

void vApplicationIdleHook(void)
{

}
