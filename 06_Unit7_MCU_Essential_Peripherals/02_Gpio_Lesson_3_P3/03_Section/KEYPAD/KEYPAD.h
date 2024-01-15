/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : KEYPAD.h
// Date          : Jan 8, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include "stm32f103x6.h"
#include "GPIO.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

/*@ref Row*/
#define HKP_ROWS_SIZE 			4
/*@ref Columns*/
#define HKP_COLUMNS_SIZE 		4
#define HKP_LOOP_STARTING_VALUE 0


/*___________________________________________________________________________________________*/

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	GPIO_registerMap_t 	  *uddtRowsPorts[HKP_ROWS_SIZE];
	GPIO_registerMap_t    *uddtColumnsPorts[HKP_COLUMNS_SIZE];
	MGPIO_uddtPinNumber_t uddtRowsPins[HKP_ROWS_SIZE];
	MGPIO_uddtPinNumber_t uddtColumnsPins[HKP_COLUMNS_SIZE];
}HKP_uddtCfg_t;

/*__________________________________________________________________________________________*/

//---------------------------
//@ref Module_REF_NAME_define
//---------------------------

/*@ref Row 	   : This Macro Will Store In It Number Of Rows In This Keypad */
/*@ref Columns : This Macro Will Store In It Number Of Columns In This Keypad*/

/*________________________________________________________________________________________*/

//===============================================
// APIs Supported by "MCAL GPIO DRIVER"
//===============================================

COMMON_uddtApiState_t HKP_uddtInit(HKP_uddtCfg_t *KEYPADx);

COMMON_uddtApiState_t HKP_uddtGetPressedBtn(HKP_uddtCfg_t *KEYPADx , uint8_t *pressedBtnVal);

/*________________________________________________________________________________________*/


#endif /* HAL_KEYPAD_KEYPAD_H_ */
