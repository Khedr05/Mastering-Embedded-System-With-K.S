/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : AlarmController.h
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef ALARMCONTROLLER_H_
#define ALARMCONTROLLER_H_

#include "states.h"


typedef enum
{
	AC_ALARM_ON = 0,
	AC_ALARM_OFF,
	AC_WAITING
}EN_AC_States_t;


STATE_DEFINE(AC_ALARM_OFF);
STATE_DEFINE(AC_ALARM_ON);
STATE_DEFINE(AC_WAITING);

extern void (*AC_State)();

#endif /* ALARMCONTROLLER_H_ */
