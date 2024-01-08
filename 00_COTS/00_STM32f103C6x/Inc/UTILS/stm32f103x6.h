/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : stm32f103x6.h
// Date          : Jan 5, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef STM32F103X6_H_
#define STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------

#include "common.h"

/*_________________________________________________________________*/

//-----------------------------
//Base addresses for Memories
//-----------------------------

#define  FLASH_MEMORY_BUS						0x08000000UL
#define  SYSTEM_MEMORY_BUS						0x1FFFF000UL
#define  SRAM_MEMORY_BUS						0x20000000UL

#define  PERIPHERALS_BASE						0x40000000UL
#define  CORTEX_M3_INTERNAL_PERIPHERALS_BASE    0xE0000000UL

/*___________________________________________________________________*/


//-----------------------------
//Base addresses for BUS Peripherals
//-----------------------------



//-----------------------------
//Base addresses for AHB Peripherals
//-----------------------------

// RCC

#define RCC_BASE					0x40021000UL

//-----------------------------
//Base addresses for APB1 Peripherals
//-----------------------------



//-----------------------------
//Base addresses for APB2 Peripherals
//-----------------------------

// GPIO

// A,B fully included in LQFP48 package

#define GPIOA_BASE				    0x40010800UL
#define GPIOB_BASE					0x40010C00UL

// C,D partial included in LQFP48 package

#define GPIOC_BASE				    0x40011000UL
#define GPIOD_BASE					0x40011400UL

// E not included in LQFP48 package

#define GPIOE_BASE				    0x40011800UL

// EXTI

#define EXTI_BASE					0x40010400UL

// AFIO

#define AFIO_BASE					0x40010000UL

/*______________________________________________________________________*/

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register
//-*-*-*-*-*-*-*-*-*-*-*


//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : RCC
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   CR;
	vuint32   CFGR;
	vuint32   CIR;
	vuint32   APB2RSTR;
	vuint32   APB1RSTR;
	vuint32   AHBENR;
	vuint32   APB2ENR;
	vuint32   APB1ENR;
	vuint32   BDCR;
	vuint32   CSR;
}RCC_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : GPIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   CRL;
	vuint32   CRH;
	vuint32   IDR;
	vuint32   ODR;
	vuint32   BSRR;
	vuint32   BRR;
	vuint32   LCKR;
}GPIO_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : EXTI
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   IMR;
	vuint32   EMR;
	vuint32   RTSR;
	vuint32   FTSR;
	vuint32   SWIER;
	vuint32   PR;
}EXTI_registerMap_t;

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register : AFIO
//-*-*-*-*-*-*-*-*-*-*-*

typedef struct
{
	vuint32   EVCR;
	vuint32   MAPR;
	vuint32   EXTICR1;
	vuint32   EXTICR2;
	vuint32   EXTICR3;
	vuint32   EXTICR4;
	vuint32   RESERVED0;
	vuint32   MAPR2;
}AFIO_registerMap_t;

/*__________________________________________________________________________*/

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants
//-*-*-*-*-*-*-*-*-*-*-*


#define  GPIOA       ((GPIO_registerMap_t*)GPIOA_BASE)
#define  GPIOB       ((GPIO_registerMap_t*)GPIOB_BASE)
#define  GPIOC       ((GPIO_registerMap_t*)GPIOC_BASE)
#define  GPIOD       ((GPIO_registerMap_t*)GPIOD_BASE)
#define  GPIOE       ((GPIO_registerMap_t*)GPIOE_BASE)


#define RCC			 ((RCC_registerMap_t*)RCC_BASE)

#define EXTI  		 ((EXTI_registerMap_t*)EXTI_BASE)

#define AFIO  		 ((AFIO_registerMap_t*)AFIO_BASE)



/*__________________________________________________________________________*/


//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros
//-*-*-*-*-*-*-*-*-*-*-*


#define  RCC_GPIOA_CLK_EN()	(RCC->APB2ENR |= 1<<2)
#define  RCC_GPIOB_CLK_EN()	(RCC->APB2ENR |= 1<<3)
#define  RCC_GPIOC_CLK_EN()	(RCC->APB2ENR |= 1<<4)
#define  RCC_GPIOD_CLK_EN()	(RCC->APB2ENR |= 1<<5)
#define  RCC_GPIOE_CLK_EN()	(RCC->APB2ENR |= 1<<6)

#define  RCC_AFIO_CLK_EN()	(RCC->APB2ENR |= 1<<0)


/*__________________________________________________________________________*/


//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros
//-*-*-*-*-*-*-*-*-*-*-*

/*__________________________________________________________________________*/


#endif /* STM32F103X6_H_ */
