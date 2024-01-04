/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : 00_EnableExti_U6L4A3.c
// File          : regAddr.h
// Date          : 02/01/2024 12:34:19 am
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#ifndef REGADDR_H_
#define REGADDR_H_

// MCU Registers

// GPIO
// PORTB
#define GPIO_DDRB	*((vuint8 *)0x37) 
//PORTD
#define GPIO_PORTD	*((vuint8 *)0x32) 
#define GPIO_DDRD	*((vuint8 *)0x31)  
#define GPIO_PIND	*((vuint8 *)0x30) 

// EXTI
#define EXTI_MCUCR	 *((vuint8 *)0x55)
#define EXTI_MCUCSR	 *((vuint8 *)0x54)
#define EXTI_GICR	 *((vuint8 *)0x5B)
#define EXTI_GIFR	 *((vuint8 *)0x5A)

// MCU Control
#define SREG		 *((vuint8 *)0x5F)



#endif /* REGADDR_H_ */