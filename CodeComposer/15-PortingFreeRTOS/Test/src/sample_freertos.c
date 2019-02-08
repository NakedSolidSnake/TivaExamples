/*
 * sample_freertos.c
 *
 *  Created on: 9 de jan de 2019
 *      Author: solid
 */


#ifdef TEST_FREE_RTOS

#include "test.h"
#include "FreeRTOS.h"
#include "task.h"

void vTask(void *args)
{
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500);
    static int count = 0;
    while(1)
    {
        count++;
        vTaskDelay(xDelay500ms);
    }
}

int Test_FreeRTOS(void)
{

    BaseType_t taskResult = xTaskCreate(vTask, "Task1", 1000, NULL, 1, NULL);

    if(taskResult == NULL)
    {
        while(1);
    }
    vTaskStartScheduler();
    return 0;
}

#endif
