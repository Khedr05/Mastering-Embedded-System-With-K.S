/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 03_EnableExti_U6L4A2
// File          : main.c
// Date          : Dec 31, 2023
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "../Inc/stdTypes.h"

// RCC registers

#define RCC_BASE	    0x40021000
#define RCC_APB2ENR		*(vuint32 *)(RCC_BASE + 0x18)


// GPIOA registers

#define GPIOA_BASE		0x40010800
#define GPIOA_CRL		*(vuint32 *)(GPIOA_BASE)
#define GPIOA_CRH		*(vuint32 *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR		*(vuint32 *)(GPIOA_BASE + 0x0C)

// EXTI registers

#define EXTI_BASE		0x40010400
#define EXTI_IMR		*(vuint32 *)(EXTI_BASE )
#define EXTI_RTSR		*(vuint32 *)(EXTI_BASE + 0x08)
#define EXTI_FTSR		*(vuint32 *)(EXTI_BASE + 0x0C)
#define EXTI_PR			*(vuint32 *)(EXTI_BASE + 0x14)

// AFIO registers
#define AFIO_BASE	 	0x40010000
#define AFIO_EXTICR1 	*(vuint32 *)(AFIO_BASE + 0x08)

// NCIV registers

#define NVIC_ISER0  	*(vuint32 *)(0xE000E100)


void vCLOCK_init(void);
void vGPIO_init(void);
void vEXTI_config(void);

int main(void)
{
	vCLOCK_init();
	vGPIO_init();
	vEXTI_config();

	while(1);

	return 0;
}

void vCLOCK_init(void)
{
	// Enable IO Port A Clock
	RCC_APB2ENR |= 1<<2;
	// Enable AFIO Clock
	RCC_APB2ENR |= (1<<0);

}

void vGPIO_init(void)
{

	// Initialise PA13 as output
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	// Initialise PA0 as output
	GPIOA_CRL |= (1<<2);
}

void vEXTI_config(void)
{
	// Select PA for EXTI0
	AFIO_EXTICR1 = 0x0;
	// Rising Trigger EXTI0
	EXTI_RTSR |= (1<<0);
	// Enable Mask EXTI0
	EXTI_IMR |= (1<<0);
	// Enable NVIC IRQ 6 (EXTI0)
	NVIC_ISER0 |= (1<<6);
}



void EXTI0_IRQHandler(void)
{
	// Toggle Led
	GPIOA_ODR ^= (1<<13);
	// Clear EXTI0 Pending Request
	EXTI_PR |= (1<<0);
}





