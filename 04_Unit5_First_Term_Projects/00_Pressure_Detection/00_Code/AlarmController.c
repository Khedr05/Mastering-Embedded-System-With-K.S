/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : AlarmController.c
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "AlarmController.h"
#include "driver.h"

static EN_AC_States_t ACCurrentState;

void (*AC_State)();

void StartAlarm()
{
	// set current state
	ACCurrentState = AC_ALARM_ON;
	// set the new state
	AC_State = STATE(AC_ALARM_ON);
	AC_State();
}
void StopAlarm()
{
	// set current state
	ACCurrentState = AC_ALARM_OFF;
	// set the new state
	AC_State = STATE(AC_ALARM_OFF);
	AC_State();
}

STATE_DEFINE(AC_ALARM_OFF)
{
	// set the alarm to off
	Set_Alarm_actuator(AC_ALARM_OFF);
	// set new state
	AC_State = STATE(AC_WAITING);
}

STATE_DEFINE(AC_ALARM_ON)
{
	// set the alarm to on
	Set_Alarm_actuator(AC_ALARM_ON);
	// set new state
	AC_State = STATE(AC_WAITING);
}

STATE_DEFINE(AC_WAITING)
{

  //set current state
  ACCurrentState = AC_WAITING;
  //set the new state in the pointer
  AC_State = STATE(AC_WAITING);
}
