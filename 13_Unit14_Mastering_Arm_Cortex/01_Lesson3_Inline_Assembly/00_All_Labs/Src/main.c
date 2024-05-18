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

uint32 controlReg = 0;
uint32 ipsrReg = 0;
uint8 IRQFlag = 0;

void EXTI9_CALLBACK(void)
{
	IRQFlag = 1;
	// Lab 6
	__asm("MRS %[ipsrReg],IPSR"
			:[ipsrReg]"=r"(ipsrReg));
}

int VAL1 = 3;
int VAL2 = 7;
int VAL3 = 0;



int main(void)
{
	// Clock Init
	MRCC_uddtInitClk(MRCC_HSI, MRCC_APB_PRESCALER_0, MRCC_APB_PRESCALER_0, MRCC_AHB_PRESCALER_0);
	MRCC_uddtEnablePeripheral(MRCC_AFIO);
	MRCC_uddtEnablePeripheral(MRCC_IOPB);
	// NVIC Configuration

	//MNVIC_uddtSetIRQGroup(MNVIC_GP_04_SP_04);
	//MNVIC_uddtSetIRQPriority(MNVIC_USART1_IRQ , MNVIC_GP_04_SP_04 , 1,1);

	MEXTI_uddtCfg_t ExtiP9B;

	ExtiP9B.uddtTriggerControl = MEXTI_TRIGGER_RISING;
	ExtiP9B.IRQCallback = EXTI9_CALLBACK;
	ExtiP9B.u8IRQStatus = MEXTI_UNMASKED;
	ExtiP9B.uddtPinData = EXTI9PB9;
	MEXTI_uddtInit(&ExtiP9B);

	// Lab 1 no output no input
	__asm("nop \n\t nop \n\t nop");

	// Lab 2 using output parameter mov VAL1 , 0xff
	__asm("mov %0,#0xff"
			:"=r"(VAL1)); // first output parm
	__asm("nop \n\t nop \n\t nop");

	// Lab 3 using input parameter mov r0 , val1
	__asm("mov r0,%0"
			: // first output parm
			:"r"(VAL1)); //second input parm
	__asm("nop \n\t nop \n\t nop");

	// Lab 4 using input & output parameter add VAL3,VAL1,VAL2
	__asm("add %0,%1,%2"
			:"=r"(VAL3) // first output parm
			:"r"(VAL1),"r"(VAL2)); //second input parm
	__asm("nop \n\t nop \n\t nop");

	// Lab 5 reserved registers add VAL3,VAL1,VAL2
	__asm("add %0,%1,%2"
			:"=r"(VAL3) // first output parm
			:"r"(VAL1),"r"(VAL2) //second input parm
			:"r3" );
	__asm("nop \n\t nop \n\t nop");

	// Lab 6  Read Control Reg & IPSR Reg Then Store Them In C Var
	__asm("MRS %[controlReg],CONTROL"
			:[controlReg]"=r"(controlReg));


	/////
	__asm("nop \n\t nop \n\t nop");

	while(1)
	{
		if(IRQFlag)
			IRQFlag = 1;
	}
	return 0;
}




