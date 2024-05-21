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



typedef enum
{
	privileged = 0,
	unprivileged
}cpuAccessLevel_t;

void switchCpuAccessLevel(cpuAccessLevel_t level)
{
	switch(level)
	{
	case privileged:

		// clear bit0 from control reg
		__asm("MRS R3,CONTROL \n\t"
				"LSR R3,R3,#0x1 \n\t"
				"LSL R3,R3,#0x1 \n\t"
				"MSR CONTROL,R3");
		break;

	case unprivileged:

		// set bit0 from control reg
		__asm("MRS R3,CONTROL \n\t"
				"ORR R3,R3,#0x1 \n\t"
				"MSR CONTROL,R3");

		break;
	}
}

void EXTI9_CALLBACK(void)
{
	switchCpuAccessLevel(privileged);
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

	switchCpuAccessLevel(unprivileged);

	while(1)
	{
	}
	return 0;
}




