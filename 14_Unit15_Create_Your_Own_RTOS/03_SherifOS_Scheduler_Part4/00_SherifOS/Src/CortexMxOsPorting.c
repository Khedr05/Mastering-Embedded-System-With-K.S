/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 13_SherifOS
// File          : CortexMxOsPorting.c
// Date          : May 23, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#include "CortexMxOsPorting.h"


unsigned char SystickLed;

void HardFault_Handler(void)
{
	while(1);
}
void MemManage_Handler(void)
{
	while(1);
}
void BusFault_Handler(void)
{
	while(1);
}
void UsageFault_Handler(void)
{
	while(1);
}



__attribute ((naked)) void SVC_Handler()
{
	__asm("TST LR,#4 \n\t"
			"ITE EQ \n\t"
			"MRSEQ R0,MSP \n\t"
			"MRSNE R0,PSP \n\t"
			"B SherifOS_SVC_Services");
}




void HW_init()
{
	// Initialize Clock Tree (RCC -> Systick Timer & CPU) 8MHZ
	// Init HW
	// Clock Tree
	// RCC Default Values Makes CPU Clock & Systick Timer Clock = 8MHZ
	// 8MHZ
	// 1 Count -> 0.125 us
	// X Count -> 1ms
 	// X = 8000 Count

	//decrease pendsv interrupt priority to be smaller than or equal systick timer
	//Systick have a priority 14
	__NVIC_SetPriority(PendSV_IRQn,15);
}



void triggerOsPendSV(void)
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}


void StartTicker(void)
{
	// This Clock Tree Should Be Defined In HW_init()
	// 8 MHZ
	// 1 Count -> 0.125 us
	// X Count -> 1 ms
	// X = 8000 Count

	SysTick_Config(8000);
}


void SysTick_Handler(void)
{
	SystickLed^=1;
	SherifOS_UpdateTasksWaitingTime();
	// Determine Pcurrent & Pnext
	DecideWhatNext();
	// Switch Context & Restore
	triggerOsPendSV();
}













