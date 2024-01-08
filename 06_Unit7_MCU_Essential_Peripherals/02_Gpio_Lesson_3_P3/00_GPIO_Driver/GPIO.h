/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : GPIO.h
// Date          : Jan 5, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_

//-----------------------------
//Enums Configuration References
//-----------------------------

/*@ref Pin Modes*/
typedef enum
{
	MGPIO_ANALOG_MODE = 0,
	MGPIO_INPUT_FL_MODE,
	MGPIO_INPUT_PU_MODE,
	MGPIO_INPUT_PD_MODE,
	MGPIO_OUTPUT_PP_MODE,
	MGPIO_OUTPUT_OD_MODE,
}MGPIO_uddtPinMode_t;

/*@ref Pin Number*/
typedef enum
{
	MGPIO_PIN0  = 0,
	MGPIO_PIN1,
	MGPIO_PIN2,
	MGPIO_PIN3,
	MGPIO_PIN4,
	MGPIO_PIN5,
	MGPIO_PIN6,
	MGPIO_PIN7,
	MGPIO_PIN8,
	MGPIO_PIN9,
	MGPIO_PIN10,
	MGPIO_PIN11,
	MGPIO_PIN12,
	MGPIO_PIN13,
	MGPIO_PIN14,
	MGPIO_PIN15,

}MGPIO_uddtPinNumber_t;

/*@ref Pin Speed*/
typedef enum
{
	MGPIO_10MHZ_SPEED = 1,
	MGPIO_2MHZ_SPEED,
	MGPIO_50MHZ_SPEED
}MGPIO_uddtPinSpeed_t;

/*@ref Pin Logic*/
typedef enum
{
	MGPIO_LOGIC_LOW = 0,
	MGPIO_LOGIC_HIGH
}MGPIO_uddtPinLogic_t;

/*@ref Pin Lock*/
typedef enum
{
	MGPIO_NOT_LOCKED = 0,
	MGPIO_IS_LOCKED
}MGPIO_uddtPinLock_t;
/*___________________________________________________________________________________________*/

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	GPIO_registerMap_t    *GPIOx;		 /*@ref GPIO registers map*/
	MGPIO_uddtPinNumber_t uddtPinNumber; /*@ref Pin Number*/
	MGPIO_uddtPinMode_t   uddtPinMode;   /*@ref Pin Modes*/
	MGPIO_uddtPinSpeed_t  uddtPinSpeed;  /*@ref Pin Speed*/
}GPIO_uddtPinConfig_t;

/*__________________________________________________________________________________________*/

//---------------------------
//@ref Module_REF_NAME_define
//---------------------------

/*@ref GPIO registers map
 *
 * Port configuration register low (GPIOx_CRL)
 * Port configuration register high (GPIOx_CRH)
 * Port input data register (GPIOx_IDR)
 * Port output data register (GPIOx_ODR)
 * Port bit set/reset register (GPIOx_BSRR)
 * Port bit reset register (GPIOx_BRR)
 * Port configuration lock register (GPIOx_LCKR)
 */


/* @ref Pin Modes
 *
 * 	MGPIO_ANALOG_MODE 	 : Analog mode
 *	MGPIO_INPUT_FL_MODE  : Floating input (reset state)
 * 	MGPIO_INPUT_PU_MODE  : Input with pull-up
 *	MGPIO_INPUT_PD_MODE  : Input with pull-down
 * 	MGPIO_OUTPUT_PP_MODE : General purpose output push-pull
 *	MGPIO_OUTPUT_OD_MODE : General purpose output Open-drain
 */

/* @ref Pin Number
 *
 * MGPIO_PIN0  : Pin Number 0
 * MGPIO_PIN1  : Pin Number 1
 * MGPIO_PIN2  : Pin Number 2
 * MGPIO_PIN3  : Pin Number 3
 * MGPIO_PIN4  : Pin Number 4
 * MGPIO_PIN5  : Pin Number 5
 * MGPIO_PIN6  : Pin Number 6
 * MGPIO_PIN7  : Pin Number 7
 * MGPIO_PIN8  : Pin Number 8
 * MGPIO_PIN9  : Pin Number 9
 * MGPIO_PIN10 : Pin Number 10
 * MGPIO_PIN11 : Pin Number 11
 * MGPIO_PIN12 : Pin Number 12
 * MGPIO_PIN13 : Pin Number 13
 * MGPIO_PIN14 : Pin Number 14
 * MGPIO_PIN15 : Pin Number 15
 */

/* @ref Pin Speed
 * MGPIO_10MHZ_SPEED : Output mode, max speed 10 MHz
 * MGPIO_2MHZ_SPEED  : Output mode, max speed 2 MHz
 * MGPIO_50MHZ_SPEED : Output mode, max speed 50 MHz
 */

/*@ref Pin Logic
 *
 * MGPIO_LOGIC_LOW  : Value Of The Pin Is GND (0 Volt)
 * MGPIO_LOGIC_HIGH : Value Of The Pin Is VCC (3.3 Volt)
 */

/*@ref Pin Lock
 *
 * MGPIO_NOT_LOCKED : Pin Is Not Locked
 * MGPIO_IS_LOCKED  : Pin Is Locked
 */


/*________________________________________________________________________________________*/

//===============================================
// APIs Supported by "MCAL GPIO DRIVER"
//===============================================


COMMON_uddtApiState_t MGPIO_uddtInitPin(GPIO_uddtPinConfig_t  *uddtpinConfig);
COMMON_uddtApiState_t MGPIO_uddtGetPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber , MGPIO_uddtPinLogic_t *uddtRetOfLogic);
COMMON_uddtApiState_t MGPIO_uddtSetPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber , MGPIO_uddtPinLogic_t  uddtValOfLogic);
COMMON_uddtApiState_t MGPIO_uddtTogPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber );
COMMON_uddtApiState_t MGPIO_uddtLockPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber);
COMMON_uddtApiState_t MGPIO_uddtIsPinLock(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber , MGPIO_uddtPinLock_t *uddtRetOfLock);


COMMON_uddtApiState_t MGPIO_uddtGetPort(GPIO_registerMap_t  *GPIOx , uint16 *u16RetOfLogic);
COMMON_uddtApiState_t MGPIO_uddtSetPort(GPIO_registerMap_t  *GPIOx, uint16  u16ValOfLogic);
COMMON_uddtApiState_t MGPIO_uddtResetPort(GPIO_registerMap_t  *GPIOx);

/*________________________________________________________________________________________*/



#endif /* MCAL_GPIO_GPIO_H_ */
