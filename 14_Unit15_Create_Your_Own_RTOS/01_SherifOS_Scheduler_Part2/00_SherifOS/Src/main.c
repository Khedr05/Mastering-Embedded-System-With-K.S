/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : main.c
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#include <string.h>
#include "Scheduler.h"

TaskRef_t Task1,Task2,Task3;

void task1(void)
{
	while(1)
	{
		// Task 1 Code
	}
}

void task2(void)
{
	while(1)
	{
		// Task 2 Code
	}
}

void task3(void)
{
	while(1)
	{
		// Task 3 Code
	}
}

int main(void)
{
	SherifOSErrorId_t error = NO_ERROR;
	//HW_Init (Initialize ClockTree,RestController)
	HW_init();
	if(SherifOS_init() != NO_ERROR)
		while(1);

	Task1.StackSize = 1024;
	Task1.p_TaskEntry = task1;
	Task1.priority = 3;
	strcpy(Task1.TaskName,"task1");

	Task2.StackSize = 1024;
	Task2.p_TaskEntry = task2;
	Task2.priority = 3;
	strcpy(Task2.TaskName,"task2");

	Task3.StackSize = 1024;
	Task3.p_TaskEntry = task3;
	Task3.priority = 3;
	strcpy(Task3.TaskName,"task3");

	error += SherifOS_CreateTask(&Task1);
	error += SherifOS_CreateTask(&Task2);
	error += SherifOS_CreateTask(&Task3);

	error += SherifOS_ActivateTask(&Task1);

	while(1)
	{

	}
	return 0;
}
