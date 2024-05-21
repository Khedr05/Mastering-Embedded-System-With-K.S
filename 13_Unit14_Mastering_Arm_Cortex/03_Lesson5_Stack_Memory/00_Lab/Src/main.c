/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : main.c
// Date          : Jan 5, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#include "stm32f103x6.h"
#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"
#include "EXTI.h"




#define TASKA_STACK_SIZE    100 // 100 byte
#define TASKB_STACK_SIZE    100

#define OS_SET_PSP(addr)  		__asm volatile("MOV R0,%0 \n\t MSR PSP,R0" : :"r"(addr))
#define OS_SWITCH_SP_TO_PSP		__asm volatile("MRS R0,CONTROL \n\t MOV R1,#0x02 \n\t ORR R0,R0,R1 \n\t MSR CONTROL,R0")
#define OS_SWITCH_SP_TO_MSP		__asm volatile("MRS R0,CONTROL \n\t MOV R1,#0x05 \n\t AND R0,R0,R1 \n\t MSR CONTROL,R0")
#define OS_GENERATE_EXCEPTION   __asm volatile("SVC #0x3")
#define OS_SWITCH_TO_PRIVILEGED __asm("MRS R3,CONTROL \n\t LSR R3,R3,#0x1 \n\t LSL R3,R3,#0x1 \n\t MSR CONTROL,R3")
#define OS_SWITCH_TO_UNPRIVILEGED __asm("MRS R3,CONTROL \n\t ORR R3,R3,#0x1 \n\t MSR CONTROL,R3")

extern int _estack;
// Main Stack
unsigned int _S_MSP = &_estack;
unsigned int _E_MSP;

// Process Stack Task A
unsigned int _S_PSP_TA;
unsigned int _E_PSP_TA;

// Process Stack Task B
unsigned int _S_PSP_TB;
unsigned int _E_PSP_TB;

uint8 TaskAFlag,TaskBFlag,IRQFlag = 0;

void EXTI9_CALLBACK(void)
{
	if(IRQFlag == 0)
	{
		TaskAFlag = 1;
		IRQFlag = 1;
	}
	else
	{
		TaskBFlag = 1;
		IRQFlag = 0;
	}
}

int TaskA (int a,int b,int c)
{
	return a+b+c;
}

int TaskB (int a,int b,int c)
{
	return a+b+c;
}

void SVC_Handler()
{
	OS_SWITCH_TO_PRIVILEGED;
}


void MainOs(void)
{
	// Main Stack
	_E_MSP = (_S_MSP - 512);

	// Task A
	_S_PSP_TA = (_E_MSP - 8);
	_E_PSP_TA = (_S_PSP_TA - TASKA_STACK_SIZE);

	// Task B
	_S_PSP_TB = (_E_PSP_TA - 8);
	_E_PSP_TB = (_S_PSP_TB - TASKB_STACK_SIZE);

	while(1)
	{
		__asm("NOP");
		if(TaskAFlag == 1)
		{
			// Set PSP Register = _S_PSP_TA
			OS_SET_PSP(_S_PSP_TA);
			// SP -> PSP
			OS_SWITCH_SP_TO_PSP;
			// Switch From Privileged -> Unprivileged
			OS_SWITCH_TO_UNPRIVILEGED;
			TaskAFlag = TaskA(1,2,3);
			// Switch From Unprivileged -> Privileged
			OS_GENERATE_EXCEPTION;
			// SP -> MSP
			OS_SWITCH_SP_TO_MSP;
		}
		else if(TaskBFlag == 1)
		{
			// Set PSP Register = _S_PSP_TB
			OS_SET_PSP(_S_PSP_TB);
			// SP -> PSP
			OS_SWITCH_SP_TO_PSP;
			// Switch From Privileged -> Unprivileged
			OS_SWITCH_TO_UNPRIVILEGED;
			TaskBFlag = TaskB(1,2,3);
			// Switch From Unprivileged -> Privileged
			OS_GENERATE_EXCEPTION;
			// SP -> MSP
			OS_SWITCH_SP_TO_MSP;
		}
		else{/*Do Nothing*/};
	}
}



int main(void)
{
	// Clock Init
	MRCC_uddtInitClk(MRCC_HSI, MRCC_APB_PRESCALER_0, MRCC_APB_PRESCALER_0, MRCC_AHB_PRESCALER_0);
	MRCC_uddtEnablePeripheral(MRCC_AFIO);
	MRCC_uddtEnablePeripheral(MRCC_IOPB);

	MEXTI_uddtCfg_t ExtiP9B;
	ExtiP9B.uddtTriggerControl = MEXTI_TRIGGER_RISING;
	ExtiP9B.IRQCallback = EXTI9_CALLBACK;
	ExtiP9B.u8IRQStatus = MEXTI_UNMASKED;
	ExtiP9B.uddtPinData = EXTI9PB9;
	MEXTI_uddtInit(&ExtiP9B);

	MainOs();

	while(1)
	{
		if(IRQFlag)
			IRQFlag = 1;
	}
	return 0;
}




