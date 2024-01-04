/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 01_TogLed_U7L1A2.c
// File          : main.c
// Date          : 04/01/2024 9:59:20 pm
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#define F_CPU 8000000UL
#include <util/delay.h>
#include "stdTypes.h"
#include "bitMath.h"
#include "regAddr.h"

#define BTN_NPRESSED		0
#define BTN_PRESSED			1

void vGpioInit(void);

int main(void)
{
	vGpioInit();
	while (1)
	{
		if(GET_BIT(GPIO_PIND , 0) == BTN_PRESSED)
		{
			SET_BIT(GPIO_PORTD , 4);
			_delay_ms(500);
			CLR_BIT(GPIO_PORTD , 4);
			while(GET_BIT(GPIO_PIND , 0) == BTN_PRESSED);
		}
		
		if(GET_BIT(GPIO_PIND , 1) == BTN_PRESSED)
		{
			SET_BIT(GPIO_PORTD , 5);
			_delay_ms(500);
			SET_BIT(GPIO_PORTD , 6);
			_delay_ms(500);
			SET_BIT(GPIO_PORTD , 7);
			_delay_ms(500);
			SET_BIT(GPIO_PORTD , 4);
			_delay_ms(250);
			CLR_BIT(GPIO_PORTD , 4);
			CLR_BIT(GPIO_PORTD , 7);
			_delay_ms(500);
			CLR_BIT(GPIO_PORTD , 6);
			_delay_ms(500);
			CLR_BIT(GPIO_PORTD , 5);
			SET_BIT(GPIO_PORTD , 4);
			_delay_ms(250);
			CLR_BIT(GPIO_PORTD , 4);
			while(GET_BIT(GPIO_PIND , 1) == BTN_PRESSED);
		}
		
		if(GET_BIT(GPIO_PIND , 2) == BTN_PRESSED)
		{
			SET_BIT(GPIO_PORTD , 7);
			_delay_ms(500);
			SET_BIT(GPIO_PORTD , 6);
			_delay_ms(500);
			SET_BIT(GPIO_PORTD , 5);
			_delay_ms(500);
			SET_BIT(GPIO_PORTD , 4);
			_delay_ms(250);
			CLR_BIT(GPIO_PORTD , 4);
			CLR_BIT(GPIO_PORTD , 5);
			_delay_ms(500);
			CLR_BIT(GPIO_PORTD , 6);
			_delay_ms(500);
			CLR_BIT(GPIO_PORTD , 7);
			SET_BIT(GPIO_PORTD , 4);
			_delay_ms(250);
			CLR_BIT(GPIO_PORTD , 4);
			while(GET_BIT(GPIO_PIND , 2) == BTN_PRESSED);
		}
	}
	
	return 0;
}

void vGpioInit(void)
{
	// select pin 5,6,7 as output for led
	SET_BIT(GPIO_DDRD , 7);
	SET_BIT(GPIO_DDRD , 6);
	SET_BIT(GPIO_DDRD , 5);
	// select pin 4 as output for buzzer
	SET_BIT(GPIO_DDRD , 4);
	// select pin 0,1,2 as input for push buttons
	CLR_BIT(GPIO_DDRD , 2);
	CLR_BIT(GPIO_DDRD , 1);
	CLR_BIT(GPIO_DDRD , 0);
}


