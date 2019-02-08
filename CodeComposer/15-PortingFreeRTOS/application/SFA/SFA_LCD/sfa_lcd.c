/*
 * sfa_lcd.c
 *
 *  Created on: 11 de jan de 2019
 *      Author: solid
 */


#include <hal_lcd16.h>
#include "sfa_lcd.h"
#include "FreeRTOS.h"
#include "semphr.h"

static SemaphoreHandle_t xLCDSemaphore;

int8_t SFA_LCD_Init(void)
{
    vSemaphoreCreateBinary(xLCDSemaphore);
    if(xLCDSemaphore == NULL)
        return -1;
    else{
        Lcd_Init();
        return 0;
    }

}

int8_t SFA_LCD_Write(const char *msg, int8_t line, uint8_t offset)
{
    if(xLCDSemaphore == NULL)
        return -1;

    if(xSemaphoreTake(xLCDSemaphore, portMAX_DELAY) == pdPASS )
    {
        Lcd_Print(msg, (LCD_LINE)line, offset);
        xSemaphoreGive(xLCDSemaphore);
        return 0;
    }
    return -1;
}

