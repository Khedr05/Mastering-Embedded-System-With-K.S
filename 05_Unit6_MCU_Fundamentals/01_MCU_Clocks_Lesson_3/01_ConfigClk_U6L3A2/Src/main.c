/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 01_ConfigClk_U6L3A2
// File          : main.c
// Date          : Dec 29, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "../Inc/stdTypes.h"

// define registers address

// RCC registers

#define RCC_BASE	    0x40021000
#define RCC_CFGR		*(vuint32 *)(RCC_BASE + 0x04)



void vClockInit(void)
{
	/*
		Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
		Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	*/

	RCC_CFGR |= (0b100 << 8);

	/*
	 	Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
		Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
		0xx: HCLK not divided
		100: HCLK divided by 2
		101: HCLK divided by 4
		110: HCLK divided by 8
		111: HCLK divided by 16
	*/

	RCC_CFGR |= (0b101 << 11);
}


int main(void)
{
	vClockInit();
	while(1)
	{
	}
	return 0;
}
















