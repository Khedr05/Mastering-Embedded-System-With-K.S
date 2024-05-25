/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : Scheduler.c
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#include "Fifo.h"
#include "Scheduler.h"
#include <string.h>

struct
{
	TaskRef_t *OSTasks[100]; //Sch. Table
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

typedef enum
{
	SVC_ACTIVATE_TASK = 0,
	SVC_TERMINATE_TASK,
	SVC_WAITING_TIME_TASK
}SVC_ID_t;


ST_FIFO_Buffer_t ReadyQueue;
TaskRef_t *ReadyQueueFIFO[100];

TaskRef_t SherifOS_IdleTask;




void PendSV_Handler()
{
	//=====================================
	//Save The Context Of The Current Task
	//=====================================
	//Get The Current Task "Current PSP From CPU Register" as CPU Push XPSR,...,R0
	OS_GET_PSP(OSControl.CurrentTask->current_PSP);

	//Using This Current_PSP (Pointer) To Store (R4 To R11)
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R4":"=r"(*(OSControl.CurrentTask->current_PSP)));
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R5":"=r"(*(OSControl.CurrentTask->current_PSP)));
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R6":"=r"(*(OSControl.CurrentTask->current_PSP)));
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R7":"=r"(*(OSControl.CurrentTask->current_PSP)));
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R8":"=r"(*(OSControl.CurrentTask->current_PSP)));
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R9":"=r"(*(OSControl.CurrentTask->current_PSP)));
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R10":"=r"(*(OSControl.CurrentTask->current_PSP)));
	OSControl.CurrentTask->current_PSP--;
	__asm volatile("MOV %0,R11":"=r"(*(OSControl.CurrentTask->current_PSP)));

	//Save The Current Value Of PSP
	//Already Saved In Current_PSP


	//====================================
	//Restore The Context Of The Next Task
	//====================================
	OSControl.CurrentTask = OSControl.NextTask;
	OSControl.NextTask = NULL;

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

//Handler Mode
void BubbleSort(void)
{
	unsigned int i,j,n;
	TaskRef_t* temp;
	n = OSControl.NoOfActiveTasks;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(OSControl.OSTasks[j]->priority > OSControl.OSTasks[j+1]->priority)
			{
				temp = OSControl.OSTasks[j];
				OSControl.OSTasks[j] = OSControl.OSTasks[j+1];
				OSControl.OSTasks[j+1] = temp;
			}
		}
	}
}


//Handler Mode
void SherifOS_UpdateScheduleTable(void)
{
	TaskRef_t* temp = NULL;
	TaskRef_t* Ptask = NULL;
	TaskRef_t* PnextTask = NULL;
	int i=0;
	// 1 - Bubble Sort Schedule Table OS_Control -> OSTASKS[100] (priority high then low)
	BubbleSort();
	// 2 - Free Ready Queue
	while(FIFO_uddtPopData(&ReadyQueue, &temp /* Pointer To Pointer */)!= FIFO_IS_EMPTY);
	// 3 - Update Ready Queue
	while(i<OSControl.NoOfActiveTasks)
	{
		Ptask = OSControl.OSTasks[i];
		PnextTask = OSControl.OSTasks[i+1];

		if(Ptask->TaskState != SUSPEND)
		{
			// in case we reached to the end of available OSTASKS
			if(PnextTask->TaskState == SUSPEND)
			{
				FIFO_uddtPushData(&ReadyQueue, Ptask);
				Ptask->TaskState = READY;
				break;
			}
			// if the Ptask priority > PnextTask then (lowest number is meaning higher priority)
			if(Ptask->priority < PnextTask->priority)
			{
				FIFO_uddtPushData(&ReadyQueue, Ptask);
				Ptask->TaskState = READY;
				break;
			}
			else if(Ptask->priority == PnextTask->priority)
			{
				// if the Ptask priority == PnextTask then
				// push Ptask to ready state
				// And make the ptask = PnextTask and PnextTask++
				FIFO_uddtPushData(&ReadyQueue, Ptask);
				Ptask->TaskState = READY;
			}
			else if(Ptask->priority > PnextTask->priority)
			{
				// not allowed to happen as we already reordered it by bubble sort
				break;
			}

		}
		i++;
	}
}


//Handler Mode
void DecideWhatNext(void)
{
 // if ready queue is empty && OS control->currentTask != suspend
 if(ReadyQueue.count == 0 && OSControl.CurrentTask->TaskState != SUSPEND) // FIFO Empty
 {
	 OSControl.CurrentTask->TaskState = RUNNING;
	 //add the current task again (round robin)
	 FIFO_uddtPushData(&ReadyQueue,OSControl.CurrentTask);
	 OSControl.NextTask = OSControl.CurrentTask;
 }
 else
 {
	 FIFO_uddtPopData(&ReadyQueue,&OSControl.NextTask);
	 OSControl.NextTask->TaskState = RUNNING;
	 //update ready queue (to keep round robin algorithm happen)
	 if((OSControl.CurrentTask->priority == OSControl.NextTask->priority)&&(OSControl.CurrentTask->TaskState != SUSPEND))
	 {
		 FIFO_uddtPushData(&ReadyQueue, OSControl.CurrentTask);
		 OSControl.CurrentTask->TaskState = READY;
	 }
 }


}



//Handler Mode
void OS_SVC(int *stackFrame)
{
	//r0,r1,r2,r3,r12,LR,return address (PC) and XPSR
	unsigned char SVCNumber = *((unsigned char*)(((unsigned char*)stackFrame[6])-2));
	switch(SVCNumber)
	{
	case SVC_ACTIVATE_TASK:
	case SVC_TERMINATE_TASK:
		//Update Sch Table
		SherifOS_UpdateScheduleTable();
		//OS is in running state
		if(OSControl.OsModeId == OS_RUNNING)
		{
			if(strcmp(OSControl.CurrentTask->TaskName ,"IdleTask") != 0)
			{
				//Decide What Next
				DecideWhatNext();
				//Trigger OS_PendSV (Switch Context/Restore)
				triggerOsPendSV();
			}
		}
		break;
	case SVC_WAITING_TIME_TASK:
		break;
	}
}

//Thread Mode
void SherifOS_OS_SVC_Set(SVC_ID_t SVC_ID)
{
	switch(SVC_ID)
	{
	case SVC_ACTIVATE_TASK:
		__asm("SVC #0x00");
		break;
	case SVC_TERMINATE_TASK:
		__asm("SVC #0x01");
		break;
	case SVC_WAITING_TIME_TASK:
		__asm("SVC #0x02");
		break;
	}
}


SherifOSErrorId_t SherifOS_ActivateTask(TaskRef_t *Tref)
{
	SherifOSErrorId_t error = NO_ERROR;

	Tref->TaskState = WAITING;
	SherifOS_OS_SVC_Set(SVC_ACTIVATE_TASK);

	return error;
}

SherifOSErrorId_t SherifOS_TerminateTask(TaskRef_t *Tref)
{
	SherifOSErrorId_t error = NO_ERROR;

	Tref->TaskState = SUSPEND;


	return error;
}





