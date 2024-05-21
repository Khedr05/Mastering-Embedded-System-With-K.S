/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : RCC.c
// Date          : Jan 11, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/


#include "RCC.h"



const uint8 APBPrescalerTable[8] = {0,0,0,0,1,2,3,4};
const uint8 AHBPrescalerTable[16] = {0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};


/*=============================================================================================
 * @Function Name : MRCC_uddtInitClk
 * @Brief         : Initializes the clock configuration for the MCU.
 * @Param [in]    : uddtClkSelect : Clock source selection (HSI, HSE, PLL).
 * @Param [in]    : uddtApb1Prescaler : APB1 bus prescaler configuration.
 * @Param [in]    : uddtApb2Prescaler : APB2 bus prescaler configuration.
 * @Param [in]    : uddtAhbPrescaler  : AHB bus prescaler configuration.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtInitClk(MRCC_uddtClkSource_t uddtClkSelect,
		MRCC_uddtApbPrescaler_t uddtApb1Prescaler, MRCC_uddtApbPrescaler_t uddtApb2Prescaler, MRCC_uddtAhbPrescaler_t uddtAhbPrescaler)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(((uddtClkSelect >= MRCC_HSI) && (uddtClkSelect <= MRCC_HSE))
			&&((uddtApb1Prescaler >= MRCC_APB_PRESCALER_0) && (uddtApb1Prescaler <= MRCC_APB_PRESCALER_16))
			&&((uddtApb2Prescaler >= MRCC_APB_PRESCALER_0) && (uddtApb2Prescaler <= MRCC_APB_PRESCALER_16))
			&&((uddtAhbPrescaler >= MRCC_AHB_PRESCALER_0) && (uddtAhbPrescaler <= MRCC_AHB_PRESCALER_512)))
	{
		switch(uddtClkSelect)
		{
		case MRCC_HSI:
		{
			RCC->CR &= ~(1UL << 24);
			RCC->CR &= ~(1UL << 16);
			RCC->CR |= (1<<0);
			while((((RCC->CR >> 1) & 0x01UL)) == 0x00);
			RCC->CFGR &= ~(1<<0b11UL);
			while((((RCC->CFGR) >> 2) & 0x03UL) != 0x00);
			ret = UAPI_OK;
			break;
		}
		case MRCC_HSE:
		{
			RCC->CR &= ~(1UL << 24);
			RCC->CR &= ~(1UL << 0);
			RCC->CR |= (1<<16);
			while(((RCC->CR >> 17) & 0x01UL) == 0x00);
			RCC->CFGR &= ~(1<<0b11UL);
			RCC->CFGR |= 0x01UL;
			while((((RCC->CFGR) >> 2) & 0x03UL) != 0x01);
			ret = UAPI_OK;
			break;
		}
		default : ret = UAPI_INVALID_PARM;
		}

		if(ret == UAPI_OK)
		{
			RCC->CFGR = (RCC->CFGR & ~(0b111 << 11)) | (uddtApb2Prescaler << 11);
			RCC->CFGR = (RCC->CFGR & ~(0b111 <<  8)) | (uddtApb1Prescaler <<  8);
			RCC->CFGR = (RCC->CFGR & ~(0b1111 << 4)) | (uddtAhbPrescaler  <<  4);
		}
		else{/*Do Nothing*/};
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MRCC_uddtInitPll
 * @Brief         : Initializes the PLL configuration for the MCU.
 * @Param [in]    : uddtPllSource : PLL input source selection (HSI/2, HSE).
 * @Param [in]    : uddtPllMulti  : PLL multiplication factor.
 * @Param [in]    : uddtApb1Prescaler : APB1 bus prescaler configuration.
 * @Param [in]    : uddtApb2Prescaler : APB2 bus prescaler configuration.
 * @Param [in]    : uddtAhbPrescaler  : AHB bus prescaler configuration.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtInitPll(MRCC_uddtPllSource_t uddtPllSource ,MRCC_uddtPLLMulti_t uddtPllMulti,
		MRCC_uddtApbPrescaler_t uddtApb1Prescaler ,MRCC_uddtApbPrescaler_t uddtApb2Prescaler,
		MRCC_uddtAhbPrescaler_t uddtAhbPrescaler)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(((uddtPllSource >= MRCC_PLL_HSI) && (uddtPllSource <= MRCC_PLL_HSE_DIVIDED))
			&&((uddtApb1Prescaler >= MRCC_APB_PRESCALER_0) && (uddtApb1Prescaler <= MRCC_APB_PRESCALER_16))
			&&((uddtApb2Prescaler >= MRCC_APB_PRESCALER_0) && (uddtApb2Prescaler <= MRCC_APB_PRESCALER_16))
			&&((uddtAhbPrescaler >= MRCC_AHB_PRESCALER_0) && (uddtAhbPrescaler <= MRCC_AHB_PRESCALER_512))
			&&((uddtPllMulti >= MRCC_PLL_MULTI_2) && (uddtPllMulti <= MRCC_PLL_MULTI_16)))
	{
		switch(uddtPllSource)
		{
		case MRCC_PLL_HSI:
		{
			RCC->CR &= ~(1UL << 24);
			RCC->CR &= ~(1UL << 16);
			RCC->CR |= (1<<0);
			while((((RCC->CR >> 1) & 0x01UL)) == 0x00);
			RCC->CFGR &= ~(1<<0b11UL);
			while((((RCC->CFGR) >> 2) & 0x03UL) != 0x00);
			RCC->CFGR = ((RCC->CFGR & ~(0b1111 << 18)) | (uddtPllMulti << 18));
			RCC->CFGR &=~(1UL << 16);
			RCC->CR |= (1UL << 24);
			while((((RCC->CR >> 25) & 0x01UL)) == 0x00);
			RCC->CFGR &= ~(1<<0b11UL);
			RCC->CFGR |= 0x02UL;
			while((((RCC->CFGR) >> 2) & 0x03UL) != 0x02);
			ret = UAPI_OK;
			break;
		}
		case MRCC_PLL_HSE:
		case MRCC_PLL_HSE_DIVIDED:
		{
			RCC->CR &= ~(1UL << 24);
			RCC->CR &= ~(1UL << 0);
			RCC->CR |= (1<<16);
			while(((RCC->CR >> 17) & 0x01UL) == 0x00);
			RCC->CFGR &= ~(1<<0b11UL);
			RCC->CFGR |= 0x01UL;
			while((((RCC->CFGR) >> 2) & 0x03UL) != 0x01);
			RCC->CFGR = ((RCC->CFGR & ~(0b1111 << 18)) | (uddtPllMulti << 18));
			RCC->CFGR |=(1UL << 16);
			RCC->CFGR &= ~(1UL << 17);
			if(uddtPllSource == MRCC_PLL_HSE_DIVIDED)
				RCC->CFGR |=(1UL << 17);
			RCC->CR |= (1UL << 24);
			while((((RCC->CR >> 25) & 0x01UL)) == 0x00);
			RCC->CFGR &= ~(1<<0b11UL);
			RCC->CFGR |= 0x02UL;
			while((((RCC->CFGR) >> 2) & 0x03UL) != 0x02);
			ret = UAPI_OK;
			break;
		}
		default : ret = UAPI_INVALID_PARM;
		}

		if(ret == UAPI_OK)
		{
			RCC->CFGR = (RCC->CFGR & ~(0b111 << 11)) | (uddtApb2Prescaler << 11);
			RCC->CFGR = (RCC->CFGR & ~(0b111 <<  8)) | (uddtApb1Prescaler <<  8);
			RCC->CFGR = (RCC->CFGR & ~(0b1111 << 4)) | (uddtAhbPrescaler  <<  4);
		}
		else{/*Do Nothing*/};
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}
	return ret;
}


/*=============================================================================================
 * @Function Name : MRCC_uddtEnablePeripheral
 * @Brief         : Enables a specific peripheral.
 * @Param [in]    : uddtPeripheral : Peripheral to be enabled.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtEnablePeripheral(MRCC_uddtPeripheral_t uddtPeripheral)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((uddtPeripheral >= MRCC_DMA1) && (uddtPeripheral <= MRCC_DAC))
	{
		switch (uddtPeripheral) {
		case MRCC_DMA1: 	RCC->AHBENR |=(1<<0); 	ret =UAPI_OK;	break;
		case MRCC_DMA2:		RCC->AHBENR |=(1<<1); 	ret =UAPI_OK;	break;
		case MRCC_SRAM: 	RCC->AHBENR |=(1<<2); 	ret =UAPI_OK;	break;
		case MRCC_FLITF:	RCC->AHBENR |=(1<<4); 	ret =UAPI_OK;	break;
		case MRCC_CRC:  	RCC->AHBENR |=(1<<6); 	ret =UAPI_OK;	break;
		case MRCC_FSMC: 	RCC->AHBENR |=(1<<8); 	ret =UAPI_OK;	break;
		case MRCC_SDIO: 	RCC->AHBENR |=(1<<10);	ret =UAPI_OK;	break;
		case MRCC_AFIO: 	RCC->APB2ENR |=(1<<0);	ret =UAPI_OK;	break;
		case MRCC_IOPA: 	RCC->APB2ENR |=(1<<2);	ret =UAPI_OK;	break;
		case MRCC_IOPB:		RCC->APB2ENR |=(1<<3);	ret =UAPI_OK;	break;
		case MRCC_IOPC: 	RCC->APB2ENR |=(1<<4);	ret =UAPI_OK;	break;
		case MRCC_IOPD: 	RCC->APB2ENR |=(1<<5);	ret =UAPI_OK;	break;
		case MRCC_IOPE:		RCC->APB2ENR |=(1<<6);	ret =UAPI_OK;	break;
		case MRCC_IOPF:		RCC->APB2ENR |=(1<<7);	ret =UAPI_OK;	break;
		case MRCC_IOPG:		RCC->APB2ENR |=(1<<8);	ret =UAPI_OK;	break;
		case MRCC_ADC1:		RCC->APB2ENR |=(1<<9);	ret =UAPI_OK;	break;
		case MRCC_ADC2:		RCC->APB2ENR |=(1<<10);	ret =UAPI_OK;	break;
		case MRCC_TIM1:		RCC->APB2ENR |=(1<<11);	ret =UAPI_OK;	break;
		case MRCC_SPI1:		RCC->APB2ENR |=(1<<12);	ret =UAPI_OK;	break;
		case MRCC_TIM8:		RCC->APB2ENR |=(1<<13);	ret =UAPI_OK;	break;
		case MRCC_USART1:	RCC->APB2ENR |=(1<<14);	ret =UAPI_OK;	break;
		case MRCC_ADC3:		RCC->APB2ENR |=(1<<15);	ret =UAPI_OK;	break;
		case MRCC_TIM9:		RCC->APB2ENR |=(1<<19);	ret =UAPI_OK;	break;
		case MRCC_TIM10:	RCC->APB2ENR |=(1<<20);	ret =UAPI_OK;	break;
		case MRCC_TIM11:	RCC->APB2ENR |=(1<<21);	ret =UAPI_OK;	break;
		case MRCC_TIM2:		RCC->APB1ENR |=(1<<0);	ret =UAPI_OK;	break;
		case MRCC_TIM3:		RCC->APB1ENR |=(1<<1);	ret =UAPI_OK;	break;
		case MRCC_TIM4:		RCC->APB1ENR |=(1<<2);	ret =UAPI_OK;	break;
		case MRCC_TIM5:		RCC->APB1ENR |=(1<<3);	ret =UAPI_OK;	break;
		case MRCC_TIM6:		RCC->APB1ENR |=(1<<4);	ret =UAPI_OK;	break;
		case MRCC_TIM7:		RCC->APB1ENR |=(1<<5);	ret =UAPI_OK;	break;
		case MRCC_TIM12:	RCC->APB1ENR |=(1<<6);	ret =UAPI_OK;	break;
		case MRCC_TIM13:	RCC->APB1ENR |=(1<<7);	ret =UAPI_OK;	break;
		case MRCC_TIM14:	RCC->APB1ENR |=(1<<8);	ret =UAPI_OK;	break;
		case MRCC_WWDG:		RCC->APB1ENR |=(1<<11);	ret =UAPI_OK;	break;
		case MRCC_SPI2:		RCC->APB1ENR |=(1<<14);	ret =UAPI_OK;	break;
		case MRCC_SPI3:		RCC->APB1ENR |=(1<<15);	ret =UAPI_OK;	break;
		case MRCC_USART2:	RCC->APB1ENR |=(1<<17);	ret =UAPI_OK;	break;
		case MRCC_USART3:	RCC->APB1ENR |=(1<<18);	ret =UAPI_OK;	break;
		case MRCC_USART4:	RCC->APB1ENR |=(1<<19);	ret =UAPI_OK;	break;
		case MRCC_USART5:	RCC->APB1ENR |=(1<<20);	ret =UAPI_OK;	break;
		case MRCC_I2C1:		RCC->APB1ENR |=(1<<21);	ret =UAPI_OK;	break;
		case MRCC_I2C2:		RCC->APB1ENR |=(1<<22);	ret =UAPI_OK;	break;
		case MRCC_USB:		RCC->APB1ENR |=(1<<23);	ret =UAPI_OK;	break;
		case MRCC_CAN:		RCC->APB1ENR |=(1<<25);	ret =UAPI_OK;	break;
		case MRCC_BKP:		RCC->APB1ENR |=(1<<27);	ret =UAPI_OK;	break;
		case MRCC_PWR:		RCC->APB1ENR |=(1<<28);	ret =UAPI_OK;	break;
		case MRCC_DAC:		RCC->APB1ENR |=(1<<29);	ret =UAPI_OK;	break;
		default: 			ret =UAPI_INVALID_PARM; break;
		}
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MRCC_uddtResetPeripheral
 * @Brief         : Resets a specific peripheral.
 * @Param [in]    : uddtPeripheral : Peripheral to be reset.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtResetPeripheral(MRCC_uddtPeripheral_t uddtPeripheral)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((uddtPeripheral >= MRCC_AFIO) && (uddtPeripheral <= MRCC_DAC))
	{
		switch (uddtPeripheral) {
		case MRCC_AFIO: 	RCC->APB2RSTR |=(1<<0);		ret =UAPI_OK; break;
		case MRCC_IOPA: 	RCC->APB2RSTR |=(1<<2);		ret =UAPI_OK; break;
		case MRCC_IOPB:		RCC->APB2RSTR |=(1<<3);		ret =UAPI_OK; break;
		case MRCC_IOPC: 	RCC->APB2RSTR |=(1<<4);		ret =UAPI_OK; break;
		case MRCC_IOPD: 	RCC->APB2RSTR |=(1<<5);		ret =UAPI_OK; break;
		case MRCC_IOPE:		RCC->APB2RSTR |=(1<<6);		ret =UAPI_OK; break;
		case MRCC_IOPF:		RCC->APB2RSTR |=(1<<7);		ret =UAPI_OK; break;
		case MRCC_IOPG:		RCC->APB2RSTR |=(1<<8);		ret =UAPI_OK; break;
		case MRCC_ADC1:		RCC->APB2RSTR |=(1<<9);		ret =UAPI_OK; break;
		case MRCC_ADC2:		RCC->APB2RSTR |=(1<<10);	ret =UAPI_OK; break;
		case MRCC_TIM1:		RCC->APB2RSTR |=(1<<11);	ret =UAPI_OK; break;
		case MRCC_SPI1:		RCC->APB2RSTR |=(1<<12);	ret =UAPI_OK; break;
		case MRCC_TIM8:		RCC->APB2RSTR |=(1<<13);	ret =UAPI_OK; break;
		case MRCC_USART1:	RCC->APB2RSTR |=(1<<14);	ret =UAPI_OK; break;
		case MRCC_ADC3:		RCC->APB2RSTR |=(1<<15);	ret =UAPI_OK; break;
		case MRCC_TIM9:		RCC->APB2RSTR |=(1<<19);	ret =UAPI_OK; break;
		case MRCC_TIM10:	RCC->APB2RSTR |=(1<<20);	ret =UAPI_OK; break;
		case MRCC_TIM11:	RCC->APB2RSTR |=(1<<21);	ret =UAPI_OK; break;
		case MRCC_TIM2:		RCC->APB1RSTR |=(1<<0);		ret =UAPI_OK; break;
		case MRCC_TIM3:		RCC->APB1RSTR |=(1<<1);		ret =UAPI_OK; break;
		case MRCC_TIM4:		RCC->APB1RSTR |=(1<<2);		ret =UAPI_OK; break;
		case MRCC_TIM5:		RCC->APB1RSTR |=(1<<3);		ret =UAPI_OK; break;
		case MRCC_TIM6:		RCC->APB1RSTR |=(1<<4);		ret =UAPI_OK; break;
		case MRCC_TIM7:		RCC->APB1RSTR |=(1<<5);		ret =UAPI_OK; break;
		case MRCC_TIM12:	RCC->APB1RSTR |=(1<<6);		ret =UAPI_OK; break;
		case MRCC_TIM13:	RCC->APB1RSTR |=(1<<7);		ret =UAPI_OK; break;
		case MRCC_TIM14:	RCC->APB1RSTR |=(1<<8);		ret =UAPI_OK; break;
		case MRCC_WWDG:		RCC->APB1RSTR |=(1<<11);	ret =UAPI_OK; break;
		case MRCC_SPI2:		RCC->APB1RSTR |=(1<<14);	ret =UAPI_OK; break;
		case MRCC_SPI3:		RCC->APB1RSTR |=(1<<15);	ret =UAPI_OK; break;
		case MRCC_USART2:	RCC->APB1RSTR |=(1<<17);	ret =UAPI_OK; break;
		case MRCC_USART3:	RCC->APB1RSTR |=(1<<18);	ret =UAPI_OK; break;
		case MRCC_USART4:	RCC->APB1RSTR |=(1<<19);	ret =UAPI_OK; break;
		case MRCC_USART5:	RCC->APB1RSTR |=(1<<20);	ret =UAPI_OK; break;
		case MRCC_I2C1:		RCC->APB1RSTR |=(1<<21);	ret =UAPI_OK; break;
		case MRCC_I2C2:		RCC->APB1RSTR |=(1<<22);	ret =UAPI_OK; break;
		case MRCC_USB:		RCC->APB1RSTR |=(1<<23);	ret =UAPI_OK; break;
		case MRCC_CAN:		RCC->APB1RSTR |=(1<<25);	ret =UAPI_OK; break;
		case MRCC_BKP:		RCC->APB1RSTR |=(1<<27);	ret =UAPI_OK; break;
		case MRCC_PWR:		RCC->APB1RSTR |=(1<<28);	ret =UAPI_OK; break;
		case MRCC_DAC:		RCC->APB1RSTR |=(1<<29);	ret =UAPI_OK; break;
		default: 			ret =UAPI_INVALID_PARM; break;
		}
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MRCC_uddtGetSysFreq
 * @Brief         : Retrieves the system frequency.
 * @Param [out]   : u32RetOfFreq : Pointer to store the retrieved system frequency.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtGetSysFreq(uint32 *u32RetOfFreq)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(u32RetOfFreq != NULL_PTR)
	{
		switch( (RCC->CFGR >> 2) & 0b11)
		{
		case MRCC_HSI:
		{
			*u32RetOfFreq = MRCC_HSI_FREQ;
			ret = UAPI_OK;
			break;
		}
		case MRCC_HSE:
		{
			*u32RetOfFreq = MRCC_HSE_FREQ;
			ret = UAPI_OK;
			break;
		}
		case MRCC_PLL:
		{
			if(((RCC->CFGR >> 16) & 0x01) == 0x00)
			{
				MRCC_uddtPLLMulti_t uddtPllMultiVal;
				uddtPllMultiVal = ((RCC->CFGR >> 18) & 0b1111);
				*u32RetOfFreq = (MRCC_HSI_FREQ /2) * uddtPllMultiVal;
				ret = UAPI_OK;
			}
			else if(((RCC->CFGR >> 16) & 0x01) == 0x01)
			{
				MRCC_uddtPLLMulti_t uddtPllMultiVal;
				uddtPllMultiVal = ((RCC->CFGR >> 18) & 0b1111);
				*u32RetOfFreq = MRCC_HSE_FREQ * uddtPllMultiVal;
				ret = UAPI_OK;
			}
			else
			{
				ret = UAPI_INVALID_PARM;
			}
			break;
		}
		default : ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MRCC_uddtGetAhbFreq
 * @Brief         : Retrieves the AHB bus frequency.
 * @Param [out]   : u32RetOfFreq : Pointer to store the retrieved AHB bus frequency.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtGetAhbFreq(uint32 *u32RetOfFreq)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(u32RetOfFreq != NULL_PTR)
	{
		uint32 u32SysFreq;
		ret = MRCC_uddtGetSysFreq(&u32SysFreq);
		*u32RetOfFreq = u32SysFreq >> AHBPrescalerTable[((RCC->CFGR >> 4) & 0x0F)];
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MRCC_uddtGetAbp1Freq
 * @Brief         : Retrieves the APB1 bus frequency.
 * @Param [out]   : u32RetOfFreq : Pointer to store the retrieved APB1 bus frequency.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtGetAbp1Freq(uint32 *u32RetOfFreq)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(u32RetOfFreq != NULL_PTR)
	{
		uint32 u32SysFreq;
		ret = MRCC_uddtGetSysFreq(&u32SysFreq);
		*u32RetOfFreq = u32SysFreq >> APBPrescalerTable[((RCC->CFGR >> 8) & 0b111)];
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MRCC_uddtGetAbp2Freq
 * @Brief         : Retrieves the APB2 bus frequency.
 * @Param [out]   : u32RetOfFreq : Pointer to store the retrieved APB2 bus frequency.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MRCC_uddtGetAbp2Freq(uint32 *u32RetOfFreq)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(u32RetOfFreq != NULL_PTR)
	{
		uint32 u32SysFreq;
		ret = MRCC_uddtGetSysFreq(&u32SysFreq);
		*u32RetOfFreq = u32SysFreq >> APBPrescalerTable[((RCC->CFGR >> 11) & 0b111)];
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}
