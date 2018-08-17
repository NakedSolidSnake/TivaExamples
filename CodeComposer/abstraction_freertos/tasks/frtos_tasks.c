
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "drivers/rgb.h"
#include "driverlib/adc.h"
#include "drivers/buttons.h"
#include "utils/uartstdio.h"
#include "priorities.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "frtos_tasks.h"
#include "driverlib/sysctl.h"
#include "modules/hal_uart.h"
#include "driverlib/timer.h"
#include "OSOperation/OSOperation.h"
#include "filter/filter.h"

#include "device_drivers/drivers/Nokia5110/Nokia5110.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

extern xQueueHandle g_pQueue;
extern xSemaphoreHandle binary_semafore;
extern xQueueHandle g_pQueueDisplay;
extern xSemaphoreHandle binary_sem_lcd;


static void vTaskAD( void *pvParameters );
static void vTaskTX( void *pvParameters );
static void vTaskTimerInterrupt(void *parameters);
static void vTaskLCDNokia5110(void *pvParameters);


#define mainDELAY_LOOP_COUNT		( 0xffff )
#define _SIZE sizeof(uint32_t)


void timerA_interrupt_handler(void){
    static unsigned long counter = 0;
    static unsigned long lcd_show = 0;
    long task_woken = 0;
    counter++;
    lcd_show++;
    TimerIntClear(TIMER0_BASE,
                  TIMER_TIMA_TIMEOUT);
    if(counter == 50){
        counter = 0;

        xSemaphoreGiveFromISR(binary_semafore, &task_woken);
    }

    if(lcd_show == 5){
        lcd_show = 0;
        xSemaphoreGiveFromISR(binary_sem_lcd, &task_woken);
    }
}



static void vTaskAD( void *pvParameters )
{
    uint32_t ui32Value;
    short adc_handle = dev_open("ADC");
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        taskENTER_CRITICAL();
        dev_ioctl(adc_handle, 0, (void *)&ui32Value);
        taskEXIT_CRITICAL();
        if(ui32Value != 0){
            (void)xQueueSend(g_pQueue, &ui32Value, portMAX_DELAY);
            taskYIELD();
        }

    }
}

static void vTaskSerial2(void *pvParameters){

    short uart2_handle = dev_open("UART2");
    for(;;){
        //print((const char *)"Serial 2\n\r");
       dev_write(uart2_handle, "Teste 1..2..3..\n\r", 0);
        taskYIELD();
    }
}

static void vTaskTimerInterrupt(void *parameters){
    uint32_t Period = 800000;
    static uint32_t time = 0;
    char convert[20];
    short timer_handle = -1;
    timer_handle = dev_open("TIMER0");
    while(1){

        if(xSemaphoreTake(binary_semafore, portMAX_DELAY)){
            sprintf(convert, "Timer one second ---> %d\n\r",time);
            time++;
            TimerLoadSet(TIMER0_BASE, TIMER_A, Period -1);
            //dev_ioctl(timer_handle, 1, (void *)&Period);
            taskENTER_CRITICAL();
            print((const char *)convert);
            taskEXIT_CRITICAL();
            taskYIELD();
        }
        else{
            taskYIELD();
        }
    }
}

static void vTaskTX( void *pvParameters )
{

    uint32_t uiRead;
    char buffer[100];
    short uart0_handle = dev_open("UART0");
    /* As per most tasks, this task is implemented in an infinite loop. */
    for( ;; )
    {
        /* Print out the name of this task. */
        if(xQueueReceive(g_pQueue, &uiRead, 0) == pdPASS){
            uiRead = TempCelsiusGrad(PID_filter(uiRead));
            sprintf(buffer, "AD_VALUE %d\n", uiRead);
            (void)xQueueSend(g_pQueueDisplay, &uiRead, portMAX_DELAY);
            dev_write(uart0_handle, buffer, 0);
        }
        taskYIELD();

    }
}


static void vTaskLCDNokia5110(void *pvParameters){


    extern const uint8_t Longhorn, Longhorn2;
    uint32_t value;
    char buffer[100];
    for(;;){
        if(xSemaphoreTake(binary_semafore, portMAX_DELAY)){
            if(xQueueReceive(g_pQueueDisplay, &value, 100) == pdPASS){
                sprintf(buffer, "ADC_VALUE.:\n%d", value);
                Nokia5110_Clear();
                Nokia5110_OutString(buffer);
            }
            else{
                taskYIELD();
            }
        }

        else{
            taskYIELD();
        }
    }

}

void CreateTasks(void) {
    /* Create one of the two tasks. */
    xTaskCreate(	vTaskAD,		/* Pointer to the function that implements the task. */
                	"Task AD",	/* Text name for the task.  This is to facilitate debugging only. */
                	configMINIMAL_STACK_SIZE * 4,		/* Stack depth - most small microcontrollers will use much less stack than this. */
                	NULL,		/* We are not using the task parameter. */
                	1,			/* This task will run at priority 1. */
                	NULL );		/* We are not using the task handle. */

    /* Create the other task in exactly the same way. */
    xTaskCreate( vTaskTX, "Task Serial", configMINIMAL_STACK_SIZE * 4, NULL, 1, NULL );
    xTaskCreate( vTaskSerial2, "Task Serial 2", configMINIMAL_STACK_SIZE * 4, NULL, 1, NULL );
    xTaskCreate( vTaskTimerInterrupt, "Task Timer", configMINIMAL_STACK_SIZE * 4, NULL, 1, NULL );
    xTaskCreate( vTaskLCDNokia5110, "Task LCD", configMINIMAL_STACK_SIZE * 4, NULL, 1, NULL );
}
