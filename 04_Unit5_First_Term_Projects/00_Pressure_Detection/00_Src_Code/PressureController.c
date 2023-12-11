/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : PressureController.c
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "PressureController.h"
#include "PressureSensor.h"
#include "AlarmController.h"
#include "driver.h"

#define THRESHOLD_VAL		20

static int currentPressure = 0;

void (*PC_State)();


void highPressureDetected()
{
	// set the state 
	PC_State = STATE(PC_HIGH_PRESSURE);
}

void setPressureVal(int val)
{
	// get the value of the pressure 
	currentPressure = val;
}

void PC_init(void)
{	
	PS_init();
	AC_State = STATE(AC_ALARM_OFF);
	PS_State = STATE(PS_READING);
	PC_State = STATE(PC_BELOW_PRESSURE);
	AC_State();
	PC_State();
}

void PC_pressureMonitor(void)
{
	while(1)
	{
		PS_State();
		if(currentPressure >= THRESHOLD_VAL)
			highPressureDetected();
		PC_State();
	}
}


STATE_DEFINE(PC_HIGH_PRESSURE)
{
	// start alarm
	StartAlarm();
	Delay(6000);
	StopAlarm();
	// set state to check the pressure again
	// set the state of sensor module to PC_BELOW_PRESSURE
	PC_State = STATE(PC_BELOW_PRESSURE);

}

STATE_DEFINE(PC_BELOW_PRESSURE)
{
	/*Do Nothing*/
}

