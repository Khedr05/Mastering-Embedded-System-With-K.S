/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : LCD.c
// Date          : Jan 8, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


//-----------------------------
//Includes
//-----------------------------

#include <stdlib.h>
#include "stm32f103x6.h"
#include "LCD.h"

/*_______________________________________________________________________________________*/

//-----------------------------
//Macros Configuration References
//-----------------------------



/*________________________________________________________________________________________*/


//---------------------------
//@ref Module_REF_NAME_define
//---------------------------

/*________________________________________________________________________________________*/

//===============================================
// APIs Supported by "MCAL GPIO DRIVER"
//===============================================

/**=============================================================================
 * @Function Name : HLCD_uddtInit
 * @Brief         : Initializes the configuration of an LCD module.
 * @Param [in]    : LCDx  : Pointer to the LCD pins configuration structure.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/

COMMON_uddtApiState_t HLCD_uddtInit(HLCD_uddtPinsCfg_t *LCDx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(LCDx != NULL_PTR)
	{

		GPIO_uddtPinConfig_t uddtPinCfg;

		uddtPinCfg.GPIOx = LCDx->uddtControlPort;
		uddtPinCfg.uddtPinNumber = LCDx->uddtRsPin;
		uddtPinCfg.uddtPinSpeed = MGPIO_10MHZ_SPEED;
		uddtPinCfg.uddtPinMode = MGPIO_OUTPUT_PP_MODE;
		uddtPinCfg.uddtPinLogic = MGPIO_LOGIC_LOW;
		ret = MGPIO_uddtInitPin(&uddtPinCfg);
		if(ret != UAPI_OK) return ret;

		uddtPinCfg.uddtPinNumber = LCDx->uddtRwPin;
		ret = MGPIO_uddtInitPin(&uddtPinCfg);
		if(ret != UAPI_OK) return ret;

		uddtPinCfg.uddtPinNumber = LCDx->uddtEnPin;
		ret = MGPIO_uddtInitPin(&uddtPinCfg);
		if(ret != UAPI_OK) return ret;


		if(LCDx->uddtDataPinsMode == HLCD_4_BIT_MODE)
		{
			/* TODO : Handling The 4bit Mode */

		}
		else if(LCDx->uddtDataPinsMode == HLCD_8_BIT_MODE)
		{
			uddtPinCfg.GPIOx = LCDx->uddtDataPort;
			for(uint8 i=0 ;i<8;i++)
			{
				uddtPinCfg.uddtPinNumber = (MGPIO_uddtPinNumber_t)i;
				ret = MGPIO_uddtInitPin(&uddtPinCfg);
				if(ret != UAPI_OK) return ret;
			}
			Udelay_ms(1);

			ret = HLCD_uddtSendCmd(LCDx,HLCD_TWO_LINE_EIGHT_BIT_MODE);
			if(ret != UAPI_OK) return ret;
			Udelay_ms(1);

			ret = HLCD_uddtSendCmd(LCDx,HLCD_CURSOR_ON);
			if(ret != UAPI_OK) return ret;
			Udelay_ms(1);

			ret = HLCD_uddtSendCmd(LCDx,HLCD_CLEAR_COMMAND);
			if(ret != UAPI_OK) return ret;
			Udelay_ms(1);

		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
 * @Function Name : HLCD_uddtSendCmd
 * @Brief         : Sends a command to the LCD module.
 * @Param [in]    : LCDx : Pointer to the LCD pins configuration structure.
 * @Param [in]    : u8Command  : The command to be sent to the LCD.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/

COMMON_uddtApiState_t HLCD_uddtSendCmd(HLCD_uddtPinsCfg_t *LCDx, uint8 u8Command)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(LCDx != NULL_PTR)
	{
		ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtRsPin,MGPIO_LOGIC_LOW);
		if(ret != UAPI_OK)  return ret;

		ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtRwPin,MGPIO_LOGIC_LOW);
		if(ret != UAPI_OK)  return ret;

		Udelay_ms(1);

		if(LCDx->uddtDataPinsMode == HLCD_4_BIT_MODE)
		{
			/* TODO : Handling The 4bit Mode */
		}
		else if(LCDx->uddtDataPinsMode == HLCD_8_BIT_MODE)
		{

			ret = MGPIO_uddtSetLeast8Pins(LCDx->uddtDataPort,u8Command);
			if(ret != UAPI_OK)  return ret;
			Udelay_ms(1);
			ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtEnPin,MGPIO_LOGIC_HIGH);
			if(ret != UAPI_OK)  return ret;
			Udelay_ms(1);
			ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtEnPin,MGPIO_LOGIC_LOW);
			if(ret != UAPI_OK)  return ret;
			Udelay_ms(1);
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}

	return ret;
}

/**=============================================================================
 * @Function Name : HLCD_uddtDisplayChar
 * @Brief         : Displays a character on the LCD module.
 * @Param [in]    : LCDx : Pointer to the LCD pins configuration structure.
 * @Param [in]    : u8Char : The character to be displayed on the LCD.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/

COMMON_uddtApiState_t HLCD_uddtDisplayChar(HLCD_uddtPinsCfg_t *LCDx, uint8 u8Char)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(LCDx != NULL_PTR)
	{
		ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtRsPin,MGPIO_LOGIC_HIGH);
		if(ret != UAPI_OK)  return ret;

		ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtRwPin,MGPIO_LOGIC_LOW);
		if(ret != UAPI_OK)  return ret;

		Udelay_ms(1);

		if(LCDx->uddtDataPinsMode == HLCD_4_BIT_MODE)
		{
			/* TODO : Handling The 4bit Mode */

		}
		else if(LCDx->uddtDataPinsMode == HLCD_8_BIT_MODE)
		{
			ret = MGPIO_uddtSetLeast8Pins(LCDx->uddtDataPort,u8Char);
			if(ret != UAPI_OK)  return ret;

			ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtEnPin,MGPIO_LOGIC_HIGH);
			if(ret != UAPI_OK)  return ret;
			Udelay_ms(1);
			ret = MGPIO_uddtSetPin(LCDx->uddtControlPort,LCDx->uddtEnPin,MGPIO_LOGIC_LOW);
			if(ret != UAPI_OK)  return ret;
			Udelay_ms(1);
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
 * @Function Name : HLCD_uddtDisplayString
 * @Brief         : Displays a string on the LCD module.
 * @Param [in]    : LCDx : Pointer to the LCD pins configuration structure.
 * @Param [in]    : u8String : Pointer to the string to be displayed on the LCD.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/

COMMON_uddtApiState_t HLCD_uddtDisplayString(HLCD_uddtPinsCfg_t *LCDx,uint8 *u8String)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((LCDx != NULL_PTR) && (u8String != NULL_PTR))
	{
			if(LCDx->uddtDataPinsMode == HLCD_4_BIT_MODE)
			{
				/* TODO : Handling The 4bit Mode */
			}
			else if(LCDx->uddtDataPinsMode == HLCD_8_BIT_MODE)
			{
				uint8 strCounter;

				for(strCounter = 0;(*(u8String+strCounter) != NULL_STR);strCounter++)
				{
					ret = HLCD_uddtDisplayChar(LCDx,(*(u8String+strCounter)));
					if(ret != UAPI_OK)  return ret;
				}
			}
			else
			{
				ret = UAPI_INVALID_PARM;
			}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
 * @Function Name : HLCD_uddtDisplayNumber
 * @Brief         : Displays a number on the LCD module.
 * @Param [in]    : LCDx : Pointer to the LCD pins configuration structure.
 * @Param [in]    : u8Number : The number to be displayed on the LCD.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/

COMMON_uddtApiState_t HLCD_uddtDisplayNumber(HLCD_uddtPinsCfg_t *LCDx, uint32 u8Number)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(LCDx != NULL_PTR)
	{
		if(LCDx->uddtDataPinsMode == HLCD_4_BIT_MODE)
		{
			/* TODO : Handling The 4bit Mode */
		}
		else if(LCDx->uddtDataPinsMode  == HLCD_8_BIT_MODE)
		{
			uint8_t bufferForNumbers[20];

			itoa(u8Number ,(char *)bufferForNumbers,10);
			ret = HLCD_uddtDisplayString(LCDx,(uint8*)bufferForNumbers);
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
 * @Function Name : HLCD_uddtChangeCursorPosition
 * @Brief         : Changes the cursor position on the LCD module.
 * @Param [in]    : LCDx : Pointer to the LCD pins configuration structure.
 * @Param [in]    : u8Row : The row where the cursor should be moved.
 * @Param [in]    : u8Column : The column where the cursor should be moved.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t HLCD_uddtChangeCursorPosition(HLCD_uddtPinsCfg_t *LCDx, uint8 u8Row, uint8 u8Column)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(LCDx != NULL_PTR)
	{
		if(LCDx->uddtDataPinsMode  == HLCD_4_BIT_MODE)
		{
			/* TODO : Handling The 4bit Mode */
		}
		else if(LCDx->uddtDataPinsMode  == HLCD_8_BIT_MODE)
		{
			if (u8Row == HLCD_ROW_ZERO && u8Column< HLCD_MAX_NUMBER_OF_COLUMNS)
				ret = HLCD_uddtSendCmd(LCDx , ((u8Column & 0x0F)|0x80));
			else if (u8Row == HLCD_ROW_ONE && u8Column<HLCD_MAX_NUMBER_OF_COLUMNS)
				ret = HLCD_uddtSendCmd(LCDx, ((u8Column & 0x0F)|0xC0));
			else ret = UAPI_INVALID_PARM;
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
 * @Function Name : HLCD_uddtShiftDisplay
 * @Brief         : Shifts the display content on the LCD module.
 * @Param [in]    : LCDx : Pointer to the LCD pins configuration structure.
 * @Param [in]    : u8ShiftIterations : Number of iterations to perform the shift.
 * @Param [in]    : u8ShiftDirection : Direction of the shift (0 for left, 1 for right).
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t HLCD_uddtShiftDisplay(HLCD_uddtPinsCfg_t *LCDx, uint8 u8ShiftIterations, uint8 u8ShiftDirection)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(LCDx != NULL_PTR)
	{
		if(u8ShiftDirection == HLCD_RIGHT || u8ShiftDirection == HLCD_LEFT)
		{
			if(LCDx->uddtDataPinsMode == HLCD_4_BIT_MODE)
			{
				/* TODO : Handling The 4bit Mode */
			}
			else if(LCDx->uddtDataPinsMode == HLCD_8_BIT_MODE)
			{
				uint8 loopCounter;
				for(loopCounter = 0;loopCounter<u8ShiftIterations;loopCounter++)
				{
					ret = HLCD_uddtSendCmd(LCDx ,u8ShiftDirection);
				}
			}
			else
			{
				ret = UAPI_INVALID_PARM;
			}
		}
		else
		{
			ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
 * @Function Name : HLCD_uddtCreateNewCustomChar
 * @Brief         : Creates a new custom character on the LCD module.
 * @Param [in]    : LCDx - Pointer to the LCD pins configuration structure.
 * @Param [in]    : u8ArrayOfChar - Pointer to an array representing the custom character pattern.
 * @Param [in]    : u8CgramPosition - CGRAM position where the custom character will be stored (0-7).
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t HLCD_uddtCreateNewCustomChar(HLCD_uddtPinsCfg_t *LCDx, uint8 *u8ArrayOfChar, uint8 u8CgramPosition)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((LCDx != NULL_PTR) && (u8ArrayOfChar != NULL_PTR))
	{
			if((u8CgramPosition >= 0) && (u8CgramPosition <= 7))
			{
				if(LCDx->uddtDataPinsMode == HLCD_4_BIT_MODE)
				{
					/* TODO : Handling The 4bit Mode */
				}
				else if(LCDx->uddtDataPinsMode == HLCD_8_BIT_MODE)
				{
					uint8 loopCounter;

					ret = HLCD_uddtSendCmd(LCDx, HLCD_SET_CGRAM_LOCATION|(u8CgramPosition*8));
					if(ret != UAPI_OK)  return ret;
					for(loopCounter = 0;loopCounter<8;loopCounter++)
					{
						ret = HLCD_uddtDisplayChar(LCDx,u8ArrayOfChar[loopCounter]);
						if(ret != UAPI_OK)  return ret;
					}

					ret = HLCD_uddtSendCmd(LCDx,HLCD_SET_CURSOR_LOCATION);
				}
				else
				{
					ret = UAPI_INVALID_PARM;
				}
			}
			else
			{
				ret = UAPI_INVALID_PARM;
			}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
* @Function Name : HLCD_uddtClr
* @Brief         : Clears the display on the LCD module.
* @Param [in]    : LCDx : Pointer to the LCD pins configuration structure.
* @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
*=============================================================================**/
COMMON_uddtApiState_t HLCD_uddtClr(HLCD_uddtPinsCfg_t *LCDx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(LCDx != NULL_PTR)
	{
		ret = HLCD_uddtSendCmd(LCDx,HLCD_CLEAR_COMMAND);
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/*________________________________________________________________________________________*/

