/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : main.c
// Date          : Jan 5, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "stm32f103x6.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "RCC.h"

int main(void)
{
	uint32 FREQ;
	MRCC_uddtInitPll(MRCC_PLL_HSI,MRCC_PLL_MULTI_15,MRCC_APB_PRESCALER_4,MRCC_APB_PRESCALER_4,MRCC_AHB_PRESCALER_2);
	MRCC_uddtEnablePeripheral(MRCC_IOPA);
	MRCC_uddtEnablePeripheral(MRCC_IOPB);
	MRCC_uddtGetSysFreq(&FREQ);
	MRCC_uddtGetAhbFreq(&FREQ);
	MRCC_uddtGetAbp1Freq(&FREQ);
	MRCC_uddtGetAbp2Freq(&FREQ);

	while(1)
	{

	}
	return 0;
}


//void vCLOCK_init(void);
//
//HLCD_uddtPinsCfg_t  uddtMyLcd =
//{
//		.uddtControlPort = GPIOA,
//		.uddtDataPinsMode = HLCD_8_BIT_MODE,
//		.uddtDataPort = GPIOA,
//		.uddtEnPin = MGPIO_PIN10,
//		.uddtRsPin = MGPIO_PIN8,
//		.uddtRwPin = MGPIO_PIN9
//};
//
//
//HKP_uddtCfg_t uddtmyKeypad =
//{
//		.uddtColumnsPorts = {GPIOB,GPIOB,GPIOB,GPIOB},
//		.uddtColumnsPins = {MGPIO_PIN5,MGPIO_PIN6,MGPIO_PIN7,MGPIO_PIN8},
//		.uddtRowsPorts = {GPIOB,GPIOB,GPIOB,GPIOB},
//		.uddtRowsPins = {MGPIO_PIN0,MGPIO_PIN1,MGPIO_PIN3,MGPIO_PIN4},
//
//};
//
//
//
//int main(void)
//{
//	vCLOCK_init();
//	uint8 c = '#';
//	HKP_uddtInit(&uddtmyKeypad);
//	HLCD_uddtInit(&uddtMyLcd);
//	HLCD_uddtDisplayChar(&uddtMyLcd, 's');
//	while(1)
//	{
//		HKP_uddtGetPressedBtn(&uddtmyKeypad , &c);
//		if(c !='#')
//		{
//			HLCD_uddtClr(&uddtMyLcd);
//			HLCD_uddtDisplayChar(&uddtMyLcd,c);
//			c = '#';
//		}
//	}
//
//	return 0;
//}
//
//void vCLOCK_init(void)
//{
//		RCC_GPIOA_CLK_EN();
//		RCC_GPIOB_CLK_EN();
//}


