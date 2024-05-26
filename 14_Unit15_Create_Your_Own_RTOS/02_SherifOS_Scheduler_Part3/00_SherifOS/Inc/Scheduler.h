/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : Scheduler.h
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "CortexMxOsPorting.h"

typedef enum
{
	NO_ERROR = 0,
	READY_QUEUE_INIT_ERROR,
	TASK_EXCEEDED_STACK_SIZE_ERROR,
}SherifOSErrorId_t;


typedef struct
{
	unsigned int StackSize;
	unsigned char priority;
	void(*p_TaskEntry)(void); // Pointer To Task C Function
	unsigned char AutoStart;
	unsigned int _S_PSP_Task; // Not Entered By The User
	unsigned int _E_PSP_Task; // Not Entered By The User
	unsigned int *current_PSP; // Not Entered By The User
	char TaskName[30];
	enum
	{
		SUSPEND = 0,
		RUNNING,
		WAITING,
		READY
	}TaskState; // Not Entered By The User

	struct
	{
		enum
		{
			ENABLE = 0,
			DISABLE
		}Blocking;
		unsigned int TicksCount;
	}TimingWaiting;


}TaskRef_t;

//APIs
SherifOSErrorId_t SherifOS_init(void);
SherifOSErrorId_t SherifOS_CreateTask(TaskRef_t *Tref);
SherifOSErrorId_t SherifOS_ActivateTask(TaskRef_t *Tref);
SherifOSErrorId_t SherifOS_TerminateTask(TaskRef_t *Tref);
SherifOSErrorId_t SherifOS_StartOs(void);
void IdleTask(void);


#endif /* SCHEDULER_H_ */
