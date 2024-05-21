/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : EXTI.c
// Date          : Jan 16, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#include "EXTI.h"

#define AFIO_GPIO_EXTI_MAPPING(REG)   ((REG == GPIOA)?0:\
		(REG == GPIOB)?1:\
				(REG == GPIOC)?2:\
						(REG == GPIOD)?3:0)

static void(*GP_IRQ_Callback[15])(void);

COMMON_uddtApiState_t  MEXTI_uddtUpdate(MEXTI_uddtCfg_t *EXTIx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(EXTIx != NULL_PTR)
	{
		MGPIO_uddtPinConfig_t ExtiPin;

		ExtiPin.uddtPinMode = MGPIO_INPUT_AF_MODE;
		ExtiPin.uddtPinNumber = EXTIx->uddtPinData.uddtPinNumber;
		ExtiPin.GPIOx = EXTIx->uddtPinData.uddtGpioPort;

		ret = MGPIO_uddtInitPin(&ExtiPin);

		if(ret != UAPI_OK) return ret;

		uint8 AFIO_EXTICR_index = EXTIx->uddtPinData.uddtLine / 4;
		uint8 AFIO_EXTICR_position = (EXTIx->uddtPinData.uddtLine % 4) *4;
		AFIO->EXTICRx[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_position);
		AFIO->EXTICRx[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_MAPPING(EXTIx->uddtPinData.uddtGpioPort) & 0xF) << AFIO_EXTICR_position);

		EXTI->RTSR &=~(1<<EXTIx->uddtPinData.uddtLine);
		EXTI->FTSR &=~(1<<EXTIx->uddtPinData.uddtLine);

		if(EXTIx->uddtTriggerControl == MEXTI_TRIGGER_RISING)
		{
			EXTI->RTSR |= (1<<EXTIx->uddtPinData.uddtLine);
		}
		else if(EXTIx->uddtTriggerControl == MEXTI_TRIGGER_FALLING)
		{
			EXTI->FTSR |= (1<<EXTIx->uddtPinData.uddtLine);
		}
		else if(EXTIx->uddtTriggerControl == MEXTI_TRIGGER_BOTH)
		{
			EXTI->RTSR |= (1<<EXTIx->uddtPinData.uddtLine);
			EXTI->FTSR |= (1<<EXTIx->uddtPinData.uddtLine);
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}

		GP_IRQ_Callback[EXTIx->uddtPinData.uddtLine] = EXTIx->IRQCallback;

		if(EXTIx->u8IRQStatus == MEXTI_UNMASKED)
		{
			ret = MEXTI_uddtUnmaskLine(EXTIx);
		}
		else if(EXTIx->u8IRQStatus == MEXTI_MASKED)
		{
			ret = MEXTI_uddtMaskLine(EXTIx);
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t   MEXTI_uddtInit(MEXTI_uddtCfg_t *EXTIx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(EXTIx != NULL_PTR)
	{
		ret = MEXTI_uddtUpdate(EXTIx);
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}


COMMON_uddtApiState_t  MEXTI_uddtSwInterrupt(MEXTI_uddtCfg_t *EXTIx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(EXTIx != NULL_PTR)
	{
		EXTI->SWIER |=(1 << EXTIx->uddtPinData.uddtLine);
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t  MEXTI_uddtMaskLine(MEXTI_uddtCfg_t *EXTIx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(EXTIx != NULL_PTR)
	{
		EXTI->IMR &= ~(1 << EXTIx->uddtPinData.uddtLine);
		ret = MNVIC_uddtDisableIRQ(EXTIx->uddtPinData.u8IvtIRQNumber);
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t  MEXTI_uddtUnmaskLine(MEXTI_uddtCfg_t *EXTIx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(EXTIx != NULL_PTR)
	{
		EXTI->IMR |= (1 << EXTIx->uddtPinData.uddtLine);
		ret = MNVIC_uddtEnableIRQ(EXTIx->uddtPinData.u8IvtIRQNumber);
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t  MEXTI_uddtReset(void)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;
	EXTI->PR = 0xFFFFFFFF;

	MNVIC_uddtDisableIRQ(MNVIC_EXTI0_IRQ);
	MNVIC_uddtDisableIRQ(MNVIC_EXTI1_IRQ);
	MNVIC_uddtDisableIRQ(MNVIC_EXTI2_IRQ);
	MNVIC_uddtDisableIRQ(MNVIC_EXTI3_IRQ);
	MNVIC_uddtDisableIRQ(MNVIC_EXTI4_IRQ);
	MNVIC_uddtDisableIRQ(MNVIC_EXTI9_5_IRQ);
	MNVIC_uddtDisableIRQ(MNVIC_EXTI15_10_IRQ);
	return ret;
}



void EXTI0_IRQHandler(void)
{
	EXTI->PR |= (1<<0);
	GP_IRQ_Callback[0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI->PR |= (1<<1);
	GP_IRQ_Callback[1]();
}

void EXTI2_IRQHandler(void)
{
	EXTI->PR |= (1<<2);
	GP_IRQ_Callback[2]();
}

void EXTI3_IRQHandler(void)
{
	EXTI->PR |= (1<<3);
	GP_IRQ_Callback[3]();
}

void EXTI4_IRQHandler(void)
{
	EXTI->PR |= (1<<4);
	GP_IRQ_Callback[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & (1<<5)){ EXTI->PR |= (1<<5); GP_IRQ_Callback[5](); }
	if(EXTI->PR & (1<<6)){ EXTI->PR |= (1<<6); GP_IRQ_Callback[6](); }
	if(EXTI->PR & (1<<7)){ EXTI->PR |= (1<<7); GP_IRQ_Callback[7](); }
	if(EXTI->PR & (1<<8)){ EXTI->PR |= (1<<8); GP_IRQ_Callback[8](); }
	if(EXTI->PR & (1<<9)){ EXTI->PR |= (1<<9); GP_IRQ_Callback[9](); }
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1<<10)){ EXTI->PR |= (1<<10); GP_IRQ_Callback[10](); }
	if(EXTI->PR & (1<<11)){ EXTI->PR |= (1<<11); GP_IRQ_Callback[11](); }
	if(EXTI->PR & (1<<12)){ EXTI->PR |= (1<<12); GP_IRQ_Callback[12](); }
	if(EXTI->PR & (1<<13)){ EXTI->PR |= (1<<13); GP_IRQ_Callback[13](); }
	if(EXTI->PR & (1<<14)){ EXTI->PR |= (1<<14); GP_IRQ_Callback[14](); }
	if(EXTI->PR & (1<<15)){ EXTI->PR |= (1<<15); GP_IRQ_Callback[15](); }
}

