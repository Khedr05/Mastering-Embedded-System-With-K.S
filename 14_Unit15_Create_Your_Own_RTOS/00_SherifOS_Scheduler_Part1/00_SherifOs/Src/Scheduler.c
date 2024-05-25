/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : Scheduler.c
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#include <string.h>
#include "Fifo.h"
#include "Scheduler.h"


struct
{
	TaskRef_t OSTasks[100]; //Sch. Table
	unsigned int _S_MSP_Task;
	unsigned int _E_MSP_Task;
	unsigned int _PSP_Task_Locator;
	unsigned int NoOfActiveTasks;
	TaskRef_t *CurrentTask;
	TaskRef_t *NextTask;
	enum
	{
		OS_SUSPEND = 0,
		OS_RUNNING
	}OsModeId;
}OSControl;

ST_FIFO_Buffer_t ReadyQueue;
TaskRef_t *ReadyQueueFIFO[100];

TaskRef_t SherifOS_IdleTask;




// To Execute Specific OS Service
void OS_SVC(int *StackFramePointer)
{
	//OS_SVC_Services -> R0 -> argument 0 = StackFramePointer
	//OS_SVC_Services : R0,R1,R2,R3,R12,LR,PC,XPSR
	unsigned char SVCNumber;
	SVCNumber = *((unsigned char *)(((unsigned char *)StackFramePointer[6])-2));

	switch(SVCNumber)
	{
	case 1:	//Active Task
		break;
	case 2:	//Terminate Task
		break;
	case 3:	//
		break;
	}
}

int OS_SVC_Set(int a,int b,int SVC_ID)
{
	int res=0;

	switch(SVC_ID)
	{
	case 1:	//Active Task
		__asm("SVC #0x01");
		break;
	case 2:	//Terminate Task
		__asm("SVC #0x02");
		break;
	case 3:	//
		__asm("SVC #0x03");
		break;
	}

	return res;
}

void PendSV_Handler()
{

}


void SherifOS_CreateMainStack(void)
{
	OSControl._S_MSP_Task = &_estack;
	OSControl._E_MSP_Task = OSControl._S_MSP_Task - MAIN_STACK_SIZE;
	//Aligned 8 Bytes Spaces Between Main Task & PSP Tasks
	OSControl._PSP_Task_Locator = (OSControl._E_MSP_Task - 8);

}



SherifOSErrorId_t SherifOS_init(void)
{
	SherifOSErrorId_t error = NO_ERROR;

	//Update OS Mode (OS Suspend)
	OSControl.OsModeId = OS_SUSPEND;
	//Specify The MAIN Stack For OS
	SherifOS_CreateMainStack();
	//Create OS Ready Queue
	if(FIFO_uddtInitBuffer(&ReadyQueue,ReadyQueueFIFO,100) != FIFO_OK)
	{
		error += READY_QUEUE_INIT_ERROR;
	}
	//Configure IDLE Task

	strcpy(SherifOS_IdleTask.TaskName,"IdleTask");
	SherifOS_IdleTask.priority = 255;
	SherifOS_IdleTask.p_TaskEntry = IdleTask;
	SherifOS_IdleTask.StackSize = 300;

	error += SherifOS_CreateTask(&SherifOS_IdleTask);



	return error;
}


void IdleTask(void)
{
	while(1)
	{
		__asm("NOP");
	}
}



void SherifOS_CreateTaskStack(TaskRef_t *Tref)
{
	/* Task Frame
	 * ===========
	 * XPSR
	 * PC (Next Task Instruction Which Should Be Run)
	 * LR (Return Register Which Is Saved In CPU While TASK1 Running Before Task Switching)
	 * R12
	 * R4
	 * R3
	 * R2
	 * R1
	 * R0
	 * =====
	 * =====
	 * R5,R6,R7,R8,R9,R10,R11 (Saved / Restore )Manual
	 */

	Tref->current_PSP = Tref->_S_PSP_Task;
	Tref->current_PSP--;
	*(Tref->current_PSP) = 0x01000000; // Dummy _XPSR T-bit Should Be = 1 To Avoid Bus Fault

	Tref->current_PSP--;
	*(Tref->current_PSP) = (unsigned int)Tref->p_TaskEntry; // PC

	Tref->current_PSP--;
	*(Tref->current_PSP) = 0xFFFFFFFD; // LR (EXC_RETURN) Return To Thread Mode With PSP Stack

	for(int i=0;i<13;i++)
	{
		Tref->current_PSP--;
		*(Tref->current_PSP) = 0; // From R0 To R12

	}


}

SherifOSErrorId_t SherifOS_CreateTask(TaskRef_t *Tref)
{
	SherifOSErrorId_t error = NO_ERROR;

	// Check Task Stack Size Exceeded The PSP Stack
	// Create Its Own PSP Stack

	Tref->_S_PSP_Task = OSControl._PSP_Task_Locator;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->StackSize;

	// -			 -
	// - _S_PSP_Task -
	// -  Task Stack -
	// - _E_PSP_Task -
	// - 			 -
	// -   _eheap	 -
	// - 			 -

	if(Tref->_E_PSP_Task < (unsigned int)(&(_eheap)))
	{
		return TASK_EXCEEDED_STACK_SIZE_ERROR;
	}
	// Aligned 8 Bytes Space Between Task PSP & Other

	OSControl._PSP_Task_Locator = (Tref->_E_PSP_Task - 8);

	// Initialize PSP Task Stack
	SherifOS_CreateTaskStack(Tref);
	// Task State Update -> Suspend
	Tref->TaskState = SUSPEND;
	return error;
}










