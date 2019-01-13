/*
 * sample_sfa_lcd16.c
 *
 *  Created on: 11 de jan de 2019
 *      Author: solid
 */

#include "test.h"
#include "sfa_lcd.h"
#include "FreeRTOS.h"
#include "task.h"

typedef struct TaskData{
    const char *msg;
    const int line;
    const int offset;
}TaskData;

TaskData taskData1 = {
                          .msg = "Task 1",
                          .line = 0,
                          .offset = 0
    };

    TaskData taskData2 = {
                          .msg = "Task 2",
                          .line = 1,
                          .offset = 0
    };

void vTaskLCD_Line(void *args)
{
    TaskData *taskData = (TaskData *)args;
    const TickType_t xTicks100ms = pdMS_TO_TICKS(100);
    int8_t ret;
    while(1)
    {
        ret = SFA_LCD_Write(taskData->msg, taskData->line, taskData->offset);
//        vTaskDelay(xTicks100ms);
        taskYIELD();
    }
}

int Test_SFA_LCD16(void)
{
    int8_t ret = -1;

    ret = SFA_LCD_Init();
    if(ret < 0)
        return -1;

    BaseType_t taskResul = xTaskCreate(vTaskLCD_Line, "Task 1", 1000, (void *)&taskData1, 1, NULL);
    if(taskResul == NULL)
        return -1;

    taskResul = xTaskCreate(vTaskLCD_Line, "Task 2", 1000, (void *)&taskData2, 1, NULL);
    if(taskResul == NULL)
        return -1;

    vTaskStartScheduler();
    return 0;
}


