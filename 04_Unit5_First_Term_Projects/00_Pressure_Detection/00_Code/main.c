/*************************************************************************/
// Author        : Sherif Ashraf Khadr
// Project       : 00_Pressure_Detection
// File          : main.c
// Date          : Dec 7, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "PressureController.h"


int main(void)
{

	PC_init();
	PC_pressureMonitor();
	return 0;
}

