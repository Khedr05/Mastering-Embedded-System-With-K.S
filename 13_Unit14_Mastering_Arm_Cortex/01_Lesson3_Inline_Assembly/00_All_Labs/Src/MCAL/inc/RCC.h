/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : RCC.h
// Date          : Jan 11, 2024
// GitHub        : https://github.com/khedr05
/*************************************************************************/

#ifndef MCAL_RCC_RCC_H_
#define MCAL_RCC_RCC_H_

#include "stm32f103x6.h"


//-----------------------------
//Macros Configuration References
//-----------------------------

#define  MRCC_HSI_FREQ		8000000UL
#define  MRCC_HSE_FREQ		4000000UL

typedef enum
{
	MRCC_HSI = 0,
	MRCC_HSE,
	MRCC_PLL
}MRCC_uddtClkSource_t;

typedef enum
{
  MRCC_PLL_HSI = 0,
  MRCC_PLL_HSE,
  MRCC_PLL_HSE_DIVIDED
}MRCC_uddtPllSource_t;

/*@ref APB Bus Prescaler*/
typedef enum
{
	MRCC_APB_PRESCALER_0 = 0,
	MRCC_APB_PRESCALER_2 = 4,
	MRCC_APB_PRESCALER_4,
	MRCC_APB_PRESCALER_8,
	MRCC_APB_PRESCALER_16
}MRCC_uddtApbPrescaler_t;

/*@ref AHB Bus Prescaler*/
typedef enum
{
	MRCC_AHB_PRESCALER_0 = 0,
	MRCC_AHB_PRESCALER_2 = 8,
	MRCC_AHB_PRESCALER_4,
	MRCC_AHB_PRESCALER_8,
	MRCC_AHB_PRESCALER_16,
	MRCC_AHB_PRESCALER_64,
	MRCC_AHB_PRESCALER_128,
	MRCC_AHB_PRESCALER_256,
	MRCC_AHB_PRESCALER_512
}MRCC_uddtAhbPrescaler_t;


/*@ref PLL Multiplication*/
typedef enum
{
	MRCC_PLL_MULTI_2 = 0,
	MRCC_PLL_MULTI_3,
	MRCC_PLL_MULTI_4,
	MRCC_PLL_MULTI_5,
	MRCC_PLL_MULTI_6,
	MRCC_PLL_MULTI_7,
	MRCC_PLL_MULTI_8,
	MRCC_PLL_MULTI_9,
	MRCC_PLL_MULTI_10,
	MRCC_PLL_MULTI_11,
	MRCC_PLL_MULTI_12,
	MRCC_PLL_MULTI_13,
	MRCC_PLL_MULTI_14,
	MRCC_PLL_MULTI_15,
	MRCC_PLL_MULTI_16,
}MRCC_uddtPLLMulti_t;



/*@ref Peripheral */
typedef enum
{
	MRCC_DMA1 = 0,
	MRCC_DMA2,
	MRCC_SRAM,
	MRCC_FLITF,
	MRCC_CRC,
	MRCC_FSMC,
	MRCC_SDIO,
	MRCC_AFIO,
	MRCC_IOPA,
	MRCC_IOPB,
	MRCC_IOPC,
	MRCC_IOPD,
	MRCC_IOPE,
	MRCC_IOPF,
	MRCC_IOPG,
	MRCC_ADC1,
	MRCC_ADC2,
	MRCC_TIM1,
	MRCC_SPI1,
	MRCC_TIM8,
	MRCC_USART1,
	MRCC_ADC3,
	MRCC_TIM9,
	MRCC_TIM10,
	MRCC_TIM11,
	MRCC_TIM2,
	MRCC_TIM3,
	MRCC_TIM4,
	MRCC_TIM5,
	MRCC_TIM6,
	MRCC_TIM7,
	MRCC_TIM12,
	MRCC_TIM13,
	MRCC_TIM14,
	MRCC_WWDG,
	MRCC_SPI2,
	MRCC_SPI3,
	MRCC_USART2,
	MRCC_USART3,
	MRCC_USART4,
	MRCC_USART5,
	MRCC_I2C1,
	MRCC_I2C2,
	MRCC_USB,
	MRCC_CAN,
	MRCC_BKP,
	MRCC_PWR,
	MRCC_DAC
}MRCC_uddtPeripheral_t;




/*___________________________________________________________________________________________*/

//-----------------------------
//User type definitions (structures)
//-----------------------------



/*__________________________________________________________________________________________*/

//---------------------------
//@ref Module_REF_NAME_define
//---------------------------

/*@ref APB Bus Prescaler
* 0xx: HCLK not divided
* 100: HCLK divided by 2
* 101: HCLK divided by 4
* 110: HCLK divided by 8
* 111: HCLK divided by 16
*/

/*@ref AHB Bus Prescaler
* 0xxx: SYSCLK not divided
* 1000: SYSCLK divided by 2
* 1001: SYSCLK divided by 4
* 1010: SYSCLK divided by 8
* 1011: SYSCLK divided by 16
* 1100: SYSCLK divided by 64
* 1101: SYSCLK divided by 128
* 1110: SYSCLK divided by 256
* 1111: SYSCLK divided by 512
*/




/*________________________________________________________________________________________*/

//===============================================
// APIs Supported by "MCAL GPIO DRIVER"
//===============================================

COMMON_uddtApiState_t  MRCC_uddtInitClk(MRCC_uddtClkSource_t uddtClkSelect ,
		MRCC_uddtApbPrescaler_t uddtApb1Prescaler ,MRCC_uddtApbPrescaler_t uddtApb2Prescaler,
		MRCC_uddtAhbPrescaler_t uddtAhbPrescaler);
COMMON_uddtApiState_t MRCC_uddtInitPll(MRCC_uddtPllSource_t uddtPllSource ,MRCC_uddtPLLMulti_t uddtPllMulti,
		MRCC_uddtApbPrescaler_t uddtApb1Prescaler ,MRCC_uddtApbPrescaler_t uddtApb2Prescaler,
		MRCC_uddtAhbPrescaler_t uddtAhbPrescaler);
COMMON_uddtApiState_t  MRCC_uddtEnablePeripheral(MRCC_uddtPeripheral_t uddtPeripheral);
COMMON_uddtApiState_t  MRCC_uddtResetPeripheral(MRCC_uddtPeripheral_t uddtPeripheral);
COMMON_uddtApiState_t  MRCC_uddtGetSysFreq(uint32 *u32RetOfFreq);
COMMON_uddtApiState_t  MRCC_uddtGetAhbFreq(uint32 *u32RetOfFreq);
COMMON_uddtApiState_t  MRCC_uddtGetAbp1Freq(uint32 *u32RetOfFreq);
COMMON_uddtApiState_t  MRCC_uddtGetAbp2Freq(uint32 *u32RetOfFreq);


/*________________________________________________________________________________________*/


#endif /* MCAL_RCC_RCC_H_ */
