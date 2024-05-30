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
MutexRef_t Mutex1;
unsigned char Task1Led,Task2Led,Task3Led,Task4Led;


void task1(void)
{
	while(1)
	{
		MutexStatus_t ret;
		static char count = 0;
		ret = SherifOS_CheckMutex(&Mutex1, &Task1);
		if(ret == RELEASE)
		{
			count++;
			SherifOS_AquireMutex(&Mutex1,&Task1);
			// Task 1 Code
			Task1Led ^=1;
			if(count == 2)
			{
				Task1Led =0;
				count = 0;
				SherifOS_ReleaseMutex(&Mutex1,&Task1);
			}
			SherifOS_TaskWait(1000,&Task1);
		}
		else{/*Do Nothing*/}
	}
}

void task2(void)
{
	while(1)
	{
		MutexStatus_t ret;
		static char count = 0;
		ret = SherifOS_CheckMutex(&Mutex1, &Task2);
		if(ret == RELEASE)
		{
			count++;
			SherifOS_AquireMutex(&Mutex1,&Task2);
			// Task 2 Code
			Task2Led ^=1;
			if(count == 1)
			{
				Task2Led = 0;
				count = 0;
				SherifOS_ReleaseMutex(&Mutex1,&Task2);
			}
			SherifOS_TaskWait(2000,&Task2);
		}
	}
}

void task3(void)
{
	while(1)
	{
		MutexStatus_t ret;
		static char count = 0;
		ret = SherifOS_CheckMutex(&Mutex1, &Task3);
		if(ret == RELEASE)
		{
			count++;
			SherifOS_AquireMutex(&Mutex1,&Task3);
			// Task 3 Code
			Task3Led ^=1;
			if(count == 2)
			{
				Task3Led = 0;
				count = 0;
				SherifOS_ReleaseMutex(&Mutex1,&Task3);
			}
			SherifOS_TaskWait(3000,&Task3);
		}
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
	Task1.priority = 1;
	strcpy(Task1.TaskName,"task1");

	Task2.StackSize = 1024;
	Task2.p_TaskEntry = task2;
	Task2.priority = 2;
	strcpy(Task2.TaskName,"task2");

	Task3.StackSize = 1024;
	Task3.p_TaskEntry = task3;
	Task3.priority = 3;
	strcpy(Task3.TaskName,"task3");

	error += SherifOS_CreateTask(&Task1);
	error += SherifOS_CreateTask(&Task2);
	error += SherifOS_CreateTask(&Task3);

	error += SherifOS_ActivateTask(&Task1);
	error += SherifOS_ActivateTask(&Task2);
	error += SherifOS_ActivateTask(&Task3);

	error += SherifOS_StartOs();

	while(1)
	{

	}
	return 0;
}
