/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : LCD.h
// Date          : Jan 8, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "GPIO.h"



#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

//-----------------------------
//Macros Configuration References
//-----------------------------

#define HLCD_CLEAR_COMMAND					0x01

#define HLCD_TWO_LINE_EIGHT_BIT_MODE		0x38
#define HLCD_TWO_LINE_FOUR_BIT_MODE			0x2C

#define HLCD_CURSOR_ON						0x0E
#define HLCD_CURSOR_OFF 					0x0C
#define HLCD_SET_CURSOR_LOCATION			0x80
#define HLCD_SET_CGRAM_LOCATION				0x40

#define HLCD_MAX_NUMBER_OF_COLUMNS			16
#define HLCD_ROW_ZERO						0
#define HLCD_ROW_ONE						1

#define HLCD_RIGHT  						0x1C
#define HLCD_LEFT   						0x18

#define HLCD_FUNCTION_SET					0b00101000
#define HLCD_DISPLAY_ON_OFF					0b00001111
#define HLCD_DISPLAY_CLR					0b00000001
#define HLCD_ENTRY_MODE						0b00000110

/*@ref LCD Bit Mode*/
typedef enum
{
	HLCD_4_BIT_MODE = 0,
	HLCD_8_BIT_MODE
}HLCD_uddtLcdBitsMode_t;

/*___________________________________________________________________________________________*/


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	HLCD_uddtLcdBitsMode_t   uddtDataPinsMode;
	GPIO_registerMap_t  	 *uddtControlPort;
	GPIO_registerMap_t		 *uddtDataPort;
	MGPIO_uddtPinNumber_t	 uddtRsPin;
	MGPIO_uddtPinNumber_t	 uddtRwPin;
	MGPIO_uddtPinNumber_t	 uddtEnPin;
}HLCD_uddtPinsCfg_t;

/*__________________________________________________________________________________________*/

//---------------------------
//@ref Module_REF_NAME_define
//---------------------------

/*@ref LCD Bit Mode
 *
 * HLCD_4_BIT_MODE : Mean That LCD Will Configure As 4 Bit Mode For Data Pins
 * HLCD_8_BIT_MODE : Mean That LCD Will Configure As 8 Bit Mode For Data Pins
 */



/*________________________________________________________________________________________*/

//===============================================
// APIs Supported by "MCAL GPIO DRIVER"
//===============================================

COMMON_uddtApiState_t HLCD_uddtInit(HLCD_uddtPinsCfg_t *LCDx);
COMMON_uddtApiState_t HLCD_uddtSendCmd(HLCD_uddtPinsCfg_t *LCDx, uint8 u8Command);
COMMON_uddtApiState_t HLCD_uddtDisplayChar(HLCD_uddtPinsCfg_t *LCDx, uint8 u8Char);
COMMON_uddtApiState_t HLCD_uddtDisplayString(HLCD_uddtPinsCfg_t *LCDx,uint8 *u8String);
COMMON_uddtApiState_t HLCD_uddtDisplayNumber(HLCD_uddtPinsCfg_t *LCDx, uint32 u8Number);
COMMON_uddtApiState_t HLCD_uddtChangeCursorPosition(HLCD_uddtPinsCfg_t *LCDx, uint8 u8Row,uint8 u8Column);
COMMON_uddtApiState_t HLCD_uddtShiftDisplay(HLCD_uddtPinsCfg_t *LCDx,uint8 u8ShiftItirations,uint8 u8ShiftDirection);
COMMON_uddtApiState_t HLCD_uddtCreateNewCustomChar(HLCD_uddtPinsCfg_t *LCDx, uint8 *u8ArrayOfChar , uint8 u8CgramPosition);
COMMON_uddtApiState_t HLCD_uddtClr(HLCD_uddtPinsCfg_t *LCDx);

/*________________________________________________________________________________________*/


#endif /* HAL_LCD_LCD_H_ */
