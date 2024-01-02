/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 00_EnableExti_U6L4A3.c
// File          : main.c
// Date          : 02/01/2024 12:34:19 am
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#define F_CPU 8000000UL
#include <util/delay.h>
#include "stdTypes.h"
#include "bitMath.h"
#include "regAddr.h"

#define EXT_INT_0				__vector_1			/* External Interrupt Request 0 */
#define EXT_INT_1				__vector_2			/* External Interrupt Request 1 */
#define EXT_INT_2				__vector_3			/* External Interrupt Request 2 */
#define ISR(INT_VECT)			void INT_VECT(void) __attribute__((signal,used));\
								void INT_VECT(void)


int main(void)
{
	// Set led pins to be output
	SET_BIT(GPIO_DDRD,7);
	SET_BIT(GPIO_DDRD,6);
	SET_BIT(GPIO_DDRD,5);	
	
	// Set INT pins to be input
	CLR_BIT(GPIO_DDRB,2);
	CLR_BIT(GPIO_DDRD,1);
	CLR_BIT(GPIO_DDRD,0);
	
	/* Configure INT 1 Sense Control 
	to any logical change*/
	SET_BIT(EXTI_MCUCR , 3);
	SET_BIT(EXTI_MCUCR , 2);
	
	/* Configure INT 0 Sense Control 
	to any logical change*/
	CLR_BIT(EXTI_MCUCR , 1);
	SET_BIT(EXTI_MCUCR , 0);
	
	/* Configure INT 0 Sense Control 
	to any logical change*/
	CLR_BIT(EXTI_MCUCSR , 6);
	
	/* Enable INT 0,1,2 */
	SET_BIT(EXTI_GICR,7);
	SET_BIT(EXTI_GICR,6);
	SET_BIT(EXTI_GICR,5);
	
	/* Enable Global INT */
	SET_BIT(SREG,7);

    while (1) 
    {
		CLR_BIT(GPIO_PORTD,7);
		CLR_BIT(GPIO_PORTD,6);
		CLR_BIT(GPIO_PORTD,5);
    }
}


ISR(EXT_INT_0)
{
	SET_BIT(GPIO_PORTD,5);
	_delay_ms(1000);
}

ISR(EXT_INT_1)
{
	SET_BIT(GPIO_PORTD,6);
	_delay_ms(1000);
}

ISR(EXT_INT_2)
{
	SET_BIT(GPIO_PORTD,7);	
	_delay_ms(1000);
}

