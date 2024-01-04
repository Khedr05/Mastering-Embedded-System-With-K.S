/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 04_ToggleLed_U7L1A1
// File          : main.c
// Date          : Jan 4, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "../Inc/stdTypes.h"

// RCC registers

#define RCC_BASE	    0x40021000
#define RCC_APB2ENR		*(vuint32 *)(RCC_BASE + 0x18)
#define RCC_IOPAEN 		(1<<2)
#define RCC_IOPBEN 		(1<<3)

// GPIOA registers

#define GPIOA_BASE		0x40010800
#define GPIOA_CRL		*(vuint32 *)(GPIOA_BASE)
#define GPIOA_CRH		*(vuint32 *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(vuint32 *)(GPIOA_BASE + 0x0C)
#define GPIOA_IDR		*(vuint32 *)(GPIOA_BASE + 0x08)
#define GPIOA13			(1UL<<13)

// GPIOB registers

#define GPIOB_BASE		0x40010C00
#define GPIOB_CRL		*(vuint32 *)(GPIOB_BASE)
#define GPIOB_CRH		*(vuint32 *)(GPIOB_BASE + 0x04)
#define GPIOB_ODR		*(vuint32 *)(GPIOB_BASE + 0x0C)
#define GPIOB_IDR		*(vuint32 *)(GPIOB_BASE + 0x08)


void vCLOCK_init(void);
void vGPIO_init(void);
void vWaitMs(uint32 itr);

int main(void)
{
	vCLOCK_init();
	vGPIO_init();
	while(1)
	{
		if(((GPIOA_IDR &(1<<1))>>1) == 0)
		{
			GPIOB_ODR ^= 1<<1;
			while (((( GPIOA_IDR & (1<<1))>> 1) == 0)); // Single Pressing
		}

		if(((GPIOA_IDR & (1<<13))>> 13) == 1) // Multi Pressing
		{
			GPIOB_ODR ^= 1<<13;
		}
		vWaitMs(1);
	}

	return 0;
}

void vCLOCK_init(void)
{
	// Enable IO Port A Clock
	RCC_APB2ENR |= RCC_IOPAEN;
	// Enable IO Port B Clock
	RCC_APB2ENR |= RCC_IOPBEN;
}

void vGPIO_init(void)
{
	GPIOA_CRL = 0;
	GPIOA_CRH = 0;
	GPIOA_ODR  = 0;

	// input mode
	GPIOA_CRL &= ~(0b11 << 4);
	// floating input
	GPIOA_CRL |= (0b01<<6);

	// push pull mode
	// output mode max speed 10 MHz
	GPIOB_CRL |= (0b01 << 4);
	// General purpose output push pull
	GPIOB_CRL &= ~(0b11 << 6);

	// input mode
	GPIOA_CRH &= ~(0b11 << 20);
	// floating input
	GPIOA_CRH |= (0b01 << 22);

	// open drain
	// output mode max speed 10 MHz
	GPIOB_CRH |= (0b01 << 20);
	// output push pull
	GPIOB_CRH &= ~(0b11 << 22);

}

void vWaitMs(uint32 itr)
{
	uint32 i,j;
	for(i =0;i<itr;i++)
	{
		for(j=0;j<255;j++);
	}
}
