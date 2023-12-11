/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : PressureController.h
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#ifndef PRESSURECONTROLLER_H_
#define PRESSURECONTROLLER_H_

#include "states.h"


typedef enum
{
	PC_CHECK_PRESSURE = 0,
	PC_HIGH_PRESSURE,
	PC_BELOW_PRESSURE
}EN_PC_States_t;

STATE_DEFINE(PC_HIGH_PRESSURE);
STATE_DEFINE(PC_BELOW_PRESSURE);


extern void (*PC_State)();

void PC_init(void);
void PC_pressureMonitor(void);

#endif /* PRESSURECONTROLLER_H_ */
