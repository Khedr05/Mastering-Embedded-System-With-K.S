/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : PressureSensor.c
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "PressureSensor.h"
#include "driver.h"

static int pressureVal = 0;
static EN_PS_States_t PSCurrentState;

void (*PS_State)();

void PS_init(void)
{
	// init sensor
	GPIO_INITIALIZATION();
	// set the new state in the pointer
	PS_State = STATE(PS_READING);
}

STATE_DEFINE(PS_READING)
{
	// set current state
	PSCurrentState = PS_READING;
	// read the value of the sensor
	pressureVal = getPressureVal();
	// set the new state in the pointer
	PS_State = STATE(PS_SEND_VAL);
}

STATE_DEFINE(PS_SEND_VAL)
{
	// set current state
	PSCurrentState = PS_SEND_VAL;
	// update the value
	setPressureVal(pressureVal);
	// set the new state in the pointer
	PS_State = STATE(PS_WAITING);
}

STATE_DEFINE(PS_WAITING)
{
	// set current state
	PSCurrentState = PS_WAITING;
	// wait for the delay
	Delay(10000);
	// set the new state in the pointer
	PS_State = STATE(PS_READING);
}








