/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 00_TogglePortAPin13_U6L3A1
// File          : main.c
// Date          : Dec 29, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "../Inc/stdTypes.h"


// define registers address

// RCC registers

#define RCC_BASE	    0x40021000
#define RCC_APB2ENR		*(vuint32 *)(RCC_BASE + 0x18)


// GPIOA registers

#define GPIOA_BASE		0x40010800
#define GPIOA_CRH		*(vuint32 *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(vuint32 *)(GPIOA_BASE + 0x0C)




int main(void)
{

	// Enable IO Port A Clock

	RCC_APB2ENR |= 1<<2;

	// Initialise GPIOA

	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;

	while(1)
	{
		GPIOA_ODR |= 1<<13;
		for(int i=0; i<5000; i++); // arbitrary delay
		GPIOA_ODR &= ~(1<<13);
		for(int i=0; i<5000; i++); // arbitrary delay

	}
	return 0;
}
















