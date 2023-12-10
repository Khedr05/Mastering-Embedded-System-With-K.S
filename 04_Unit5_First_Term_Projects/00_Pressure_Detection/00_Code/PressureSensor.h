/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : PressureSensor.h
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_

#include "states.h"


typedef enum
{
	PS_READING = 0,
	PS_SEND_VAL,
	PS_WAITING
}EN_PS_States_t;

void PS_init(void);

STATE_DEFINE(PS_READING);
STATE_DEFINE(PS_SEND_VAL);
STATE_DEFINE(PS_WAITING);

extern void (*PS_State)();

#endif /* PRESSURESENSOR_H_ */
