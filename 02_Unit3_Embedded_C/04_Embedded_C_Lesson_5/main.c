/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sherif_Ashraf
 * @brief          : Main program body
 ******************************************************************************
**/

#include <stdio.h>
#include <stdlib.h>

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

void* _sbrk(int increment)
{

	static Uchar8_t *heap_ptr = NULL ;
	Uchar8_t *prev_heap_ptr = NULL ; 
	extern Uint32_t _E_BSS ; 
	extern Uint32_t _HEAP_END ;

	// first time intalized 
	if(heap_ptr == NULL)
	{
		heap_ptr = (unsigned char*)&_E_BSS ; 
	} 

	prev_heap_ptr = heap_ptr ; 

	// protect stack

	if((heap_ptr + increment) > ( (unsigned char*)&_HEAP_END ))
		return (void*) NULL ;

	// booking inc size 
	heap_ptr += increment ; 

	return (void*) prev_heap_ptr ;
}



int main(void)
{
	int *p = (int*)malloc(4);
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
	free(p);
}
