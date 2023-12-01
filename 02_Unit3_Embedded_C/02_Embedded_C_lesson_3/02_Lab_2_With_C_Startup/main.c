/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sherif_Ashraf
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

// data type libary
#include "dataTypes.h"

/* not used varibales only to take addresses */

Uchar8_t g_variables[3] = {1,2,3};
Uchar8_t const const_variables[3] = {1,2,3};
Uchar8_t BSS_VAR[3];

// registars address

#define RCC_BASE	0x40021000
#define GPIOA_BASE	0x40010800
#define RCC_APB2ENR	*(VUint32_t *)(RCC_BASE + 0x18)
#define GPIOA_CRH	*(VUint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR	*(VUint32_t *)(GPIOA_BASE + 0x0C)

// bit fields

#define RCC_IOPAEN (1<<2)
#define GPIOA13	   (1UL<<13)

typedef union
{
	VUint32_t	all_fields;
	struct
	{
		VUint32_t	reserved:13;
		VUint32_t	p_13:1;
	}pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0C);

int main(void)
{
	RCC_APB2ENR |= RCC_IOPAEN;
	GPIOA_CRH 	&= 0xFF0FFFFF;
	GPIOA_CRH	|= 0x00200000;
	while(1)
	{
		R_ODR->pin.p_13 = 1;
		for(int i = 0;i<50000;i++); // arbitrary delay
		R_ODR->pin.p_13 = 0;
		for(int i = 0;i<50000;i++); // arbitrary delay
	}
}
