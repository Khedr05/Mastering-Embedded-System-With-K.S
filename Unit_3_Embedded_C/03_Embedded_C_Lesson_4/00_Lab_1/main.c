/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sherif_Ashraf
 * @brief          : Main program body
 ******************************************************************************
**/

// data type libary
#include "dataTypes.h"

// registars address

#define SYSCTL_BASE	0x400FE000
#define GPIOF_BASE	0x40025000

#define SYSCTL_RCGC2_R	(*(VUint32_t *)(SYSCTL_BASE + 0x108))

#define GPIOF_DIR_R		(*(VUint32_t *)(GPIOF_BASE + 0x400))
#define GPIOF_DATA_R	(*(VUint32_t *)(GPIOF_BASE + 0x3FC))
#define GPIOF_DEN_R		(*(VUint32_t *)(GPIOF_BASE + 0x51C))



int main(void)
{

	volatile Uint32_t delay_count ;
	SYSCTL_RCGC2_R = 0x20 ; 
	// delay to make sure GPIOF is up and running

	for(delay_count = 0 ; delay_count < 200 ; delay_count++) ;	
	GPIOF_DIR_R |= 1<<3 ; // DIR is output for pin 3 port F
	GPIOF_DEN_R |= 1<<3 ; // enable pin 3 in port f	
	while(1)
	{
		GPIOF_DATA_R |= 1<<3 ; // out high on pin 3
		for(delay_count = 0 ; delay_count < 200000 ; delay_count++) ;	
		GPIOF_DATA_R &= ~(1<<3) ; // out low on pin 3
		for(delay_count = 0 ; delay_count < 200000 ; delay_count++) ;	
	}

	return 0 ;
}
