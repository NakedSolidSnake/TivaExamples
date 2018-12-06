/* include *******************************************************************************************/
#include <fileoperation.h>
#include <stdlib.h>

#include <bluetooth.h>
#include <keyboard.h>
#include <lcd16.h>
#include <lcd_graphics.h>
#include <serial.h>
#include <zigbee.h>
#include <adc.h>
#include <timers.h>

/* defines *******************************************************************************************/

/* global variables **********************************************************************************/

//static const ADC_Descriptor ad_descriptor = {
//	.id = 1,
//	.ad_name = (const uint8_t *)"AD Config"
//};
//
//static const Bluetooth_Descriptor bluetooth_descriptor = {
//	.id = 1,
//	.bluetooth_name = (const uint8_t *)"Bluetooth Config"
//};
//
//static const Keyboard_Descriptor keyboad_descriptor = {
//	.id = 1,
//	.keyboard_name = (const uint8_t *)"Keyboard Config"
//};

//static const LcdGraphics_Descriptor lcd_graphics_descriptor = {
//	.id = 1,
//	.lcd_graphics_name = (const uint8_t *)"Lcd Graphics Config"
//};

static const Lcd16_Descriptor lcd16_descriptor = {
	.id = 1,
	.lcd16_name = (const uint8_t *)"Lcd 16 Config"
};

static const Serial_Descriptor serial_descriptor = {
	.id = 2,
	.serial_name = (const uint8_t *)"Serial Config"
};

//static const ZigBee_Descriptor zigbee_descriptor = {
//	.id = 1,
//	.zigbee_name = (const uint8_t *)"ZigBee Descriptor"
//};

static const Timer_Descriptor timer_descriptor = {
	.id = 1,
	.timer_name = (const uint8_t *)"Timer Descriptor"
};

fileoperation devices[] = 
{
	{"TIMER"       , 0, .context = &timer_descriptor       , .open = timer_open       , .write = timer_write       , .read = timer_read       , .ioctl = timer_ioctl       , .close = timer_close},
//	{"Bluetooth"   , 0, .context = &bluetooth_descriptor   , .open = bluetooth_open   , .write = bluetooth_write   , .read = bluetooth_read   , .ioctl = bluetooth_ioctl   , .close = bluetooth_close},
//	{"Keyboard"    , 0, .context = &keyboad_descriptor     , .open = keyboard_open    , .write = keyboard_write    , .read = keyboard_read    , .ioctl = keyboard_ioctl    , .close = keyboard_close},
	{"LCD16"       , 0, .context = &lcd16_descriptor       , .open = lcd16_open       , .write = lcd16_write       , .read = lcd16_read       , .ioctl = lcd16_ioctl       , .close = lcd16_close},
//	{"LCD_Graphics", 0, .context = &lcd_graphics_descriptor, .open = lcd_graphics_open, .write = lcd_graphics_write, .read = lcd_graphics_read, .ioctl = lcd_graphics_ioctl, .close = lcd_graphics_close},
	{"SERIAL"      , 0, .context = &serial_descriptor      , .open = serial_open      , .write = serial_write      , .read = serial_read      , .ioctl = serial_ioctl      , .close = serial_close},
//	{"Zigbee"      , 0, .context = &zigbee_descriptor      , .open = zigbee_open      , .write = zigbee_write      , .read = zigbee_read      , .ioctl = zigbee_ioctl      , .close = zigbee_close},
//	{"ADC"         , 0, .context = &ad_descriptor          , .open = adc_open         , .write = adc_write         , .read = adc_read         , .ioctl = adc_ioctl         , .close = adc_close},
};


uint8_t devices_amount = sizeof(devices) / sizeof(devices[0]);
fileoperation *pDevices = devices;
