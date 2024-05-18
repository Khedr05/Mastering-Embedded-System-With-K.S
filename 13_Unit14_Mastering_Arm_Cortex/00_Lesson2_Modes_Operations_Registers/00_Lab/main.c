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


uint8 IRQFlag = 0;

void EXTI9_CALLBACK(void)
{
	IRQFlag = 1;
}

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


	while(1)
	{
		if(IRQFlag)
			IRQFlag = 1;
	}
	return 0;
}




