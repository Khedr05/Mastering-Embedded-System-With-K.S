/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 02_ConfigClk_U6L3A3
// File          : main.c
// Date          : Dec 29, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "../Inc/stdTypes.h"

// define registers address

// RCC registers

#define RCC_BASE	    0x40021000
#define RCC_CFGR		*(vuint32 *)(RCC_BASE + 0x04)
#define RCC_CR			*(vuint32 *)(RCC_BASE + 0x00)



void vClockInit(void)
{
	/*
	    Bits 1:0 SW[1:0]: System clock Switch
		Set and cleared by software to select SYSCLK source.
		Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of failure of
		the HSE oscillator used directly or indirectly as system clock (if the Clock Security System is
		enabled).
		00: HSI selected as system clock
		01: HSE selected as system clock
		10: PLL selected as system clock
		11: Not allowed

	 */

	RCC_CFGR |= (0b10 << 0);

	/*
	 	Bits 21:18 PLLMUL[3:0]: PLL multiplication factor
		These bits are written by software to define the PLL multiplication factor. They can be written only
		when PLL is disabled.
		000x: Reserved
		0010: PLL input clock x 4
		0011: PLL input clock x 5
		0100: PLL input clock x 6
		0101: PLL input clock x 7
		0110: PLL input clock x 8
		0111: PLL input clock x 9
		10xx: Reserved
		1100: Reserved
		1101: PLL input clock x 6.5
		111x: Reserved
	 */

	RCC_CFGR |= (0b0110 << 18);


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

	/*
		Bit 24 PLLON: PLL enable
		Set and cleared by software to enable PLL.
		Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
		PLL clock is used as system clock or is selected to become the system clock. Software
		must disable the USB OTG FS clock before clearing this bit.
		0: PLL OFF
		1: PLL ON
	 */

	RCC_CR |= (1 << 24);
}


int main(void)
{
	vClockInit();
	while(1)
	{
	}
	return 0;
}

