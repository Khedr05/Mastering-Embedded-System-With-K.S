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
	GPIO_INITIALIZATION(); // init sensor
	PS_State = STATE(PS_READING); 	// set the new state in the pointer
}

STATE_DEFINE(PS_READING)
{
	PSCurrentState = PS_READING; 	// set current state
	pressureVal = getPressureVal(); // read the value of the sensor
	PS_State = STATE(PS_SEND_VAL); 	// set the new state in the pointer
}

STATE_DEFINE(PS_SEND_VAL)
{
	PSCurrentState = PS_SEND_VAL; 	// set current state
	setPressureVal(pressureVal); 	// update the value
	PS_State = STATE(PS_WAITING); 	// set the new state in the pointer
}

STATE_DEFINE(PS_WAITING)
{
	PSCurrentState = PS_WAITING; 	// set current state
	Delay(10000); 	// wait for the delay
	PS_State = STATE(PS_READING); 	// set the new state in the pointer
}








