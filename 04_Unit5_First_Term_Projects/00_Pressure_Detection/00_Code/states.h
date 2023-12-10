/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : states.h
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef STATES_H_
#define STATES_H_

#include <stdio.h>
#include <stdlib.h>

//Automatic STATE Function genrated
#define STATE_DEFINE(_stateFun_) void ST_##_stateFun_()
#define STATE(_stateFun_)	ST_##_stateFun_

// Signals
void setPressureVal(int val);
void highPressureDetected();
void StartAlarm();
void StopAlarm();

#endif /* STATES_H_ */
