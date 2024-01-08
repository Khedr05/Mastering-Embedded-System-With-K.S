/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : GPIO.c
// Date          : Jan 5, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"
#include "GPIO.h"


//===============================================
// APIs Supported by "MCAL GPIO DRIVER"
//===============================================


COMMON_uddtApiState_t Get_CRLH_Position(MGPIO_uddtPinNumber_t uddtPinNumber ,uint8 *u8RetOfPosition)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(u8RetOfPosition != NULL_PTR)
	{
		if( (uddtPinNumber >= MGPIO_PIN0) && (uddtPinNumber <= MGPIO_PIN15))
		{
			switch(uddtPinNumber){
			case MGPIO_PIN0:
			case MGPIO_PIN8:
				*u8RetOfPosition = 0;
				ret = UAPI_OK;
				break;
			case MGPIO_PIN1:
			case MGPIO_PIN9:
				*u8RetOfPosition = 4;
				ret = UAPI_OK;
				break;
			case MGPIO_PIN2:
			case MGPIO_PIN10:
				*u8RetOfPosition = 8;
				ret = UAPI_OK;
				break;
			case MGPIO_PIN3:
			case MGPIO_PIN11:
				*u8RetOfPosition = 12;
				ret = UAPI_OK;
				break;
			case MGPIO_PIN4:
			case MGPIO_PIN12:
				*u8RetOfPosition = 16;
				ret = UAPI_OK;
				break;
			case MGPIO_PIN5:
			case MGPIO_PIN13:
				*u8RetOfPosition = 20;
				ret = UAPI_OK;
				break;
			case MGPIO_PIN6:
			case MGPIO_PIN14:
				*u8RetOfPosition = 24;
				ret = UAPI_OK;
				break;
			case MGPIO_PIN7:
			case MGPIO_PIN15:
				*u8RetOfPosition = 28;
				ret = UAPI_OK;
				break;
			default: ret = UAPI_INVALID_PARM;
			}
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
 * @Function Name : MGPIO_uddtInitPin
 * @Brief         : Initialises a GPIO pin according to the specified configuration.
 * @param [in]    : uddtpinConfig : Pointer to the structure containing pin configurations.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtInitPin(GPIO_uddtPinConfig_t *uddtpinConfig)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(uddtpinConfig != NULL_PTR)
	{
		uint8 u8PinPosationVal;
		vuint32 *vu32ConfigReg = NULL_PTR;
		uint8 u8PinConfigVal = 0;

		ret = Get_CRLH_Position(uddtpinConfig->uddtPinNumber ,&u8PinPosationVal);
		vu32ConfigReg = (uddtpinConfig->uddtPinNumber < 8)? (&uddtpinConfig->GPIOx->CRL):(&uddtpinConfig->GPIOx->CRH);

		(*vu32ConfigReg) &= ~(0xF << u8PinPosationVal);

		switch(uddtpinConfig->uddtPinMode)
		{
		case MGPIO_OUTPUT_OD_MODE:
		case MGPIO_OUTPUT_PP_MODE:
		{
			u8PinConfigVal = ((((uddtpinConfig->uddtPinMode - 4 ) << 2) | (uddtpinConfig->uddtPinSpeed)) & 0x0F);
			(*vu32ConfigReg) |= ((u8PinConfigVal) << u8PinPosationVal);
			ret = UAPI_OK;
			break;
		}
		case MGPIO_ANALOG_MODE:
		case MGPIO_INPUT_FL_MODE:
		{
			u8PinConfigVal = ((((uddtpinConfig->uddtPinMode ) << 2) | (0x0)) & 0x0F);
			(*vu32ConfigReg) |= ((u8PinConfigVal) << u8PinPosationVal);
			ret = UAPI_OK;
			break;
		}
		case MGPIO_INPUT_PD_MODE:
		{
			u8PinConfigVal = ((((uddtpinConfig->uddtPinMode ) << 2) | (0x0)) & 0x0F);
			SET_BIT(uddtpinConfig->GPIOx->BRR , uddtpinConfig->uddtPinNumber);
			(*vu32ConfigReg) |= ((u8PinConfigVal) << u8PinPosationVal);
			ret = UAPI_OK;
			break;
		}
		case MGPIO_INPUT_PU_MODE:
		{
			u8PinConfigVal = ((((uddtpinConfig->uddtPinMode ) << 2) | (0x0)) & 0x0F);
			SET_BIT(uddtpinConfig->GPIOx->BSRR , uddtpinConfig->uddtPinNumber);
			(*vu32ConfigReg) |= ((u8PinConfigVal) << u8PinPosationVal);
			ret = UAPI_OK;
			break;
		}
		default : ret = UAPI_INVALID_PARM;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}


/**=============================================================================
 * @brief         : Retrieves the logic state of a specific GPIO pin.
 * @param [in]    : GPIOx : Pointer to the GPIO register map for the target port.
 * @param [in]    : uddtPinNumber : The pin number to retrieve the logic state from.
 * @param [out]   : uddtRetOfLogic : Pointer to store the logic state of the GPIO pin.
 * @return        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtGetPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber , MGPIO_uddtPinLogic_t *uddtRetOfLogic)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((GPIOx != NULL_PTR) && (uddtRetOfLogic != NULL_PTR))
	{
		if((uddtPinNumber >= MGPIO_PIN0) && (uddtPinNumber <= MGPIO_PIN15))
		{
			*uddtRetOfLogic = GET_BIT(GPIOx->IDR , uddtPinNumber);
			ret = UAPI_OK;
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
 * @brief         : Sets the logic state of a specific GPIO pin.
 * @param [in]    : GPIOx : Pointer to the GPIO register map for the target port.
 * @param [in]    : uddtPinNumber : The pin number to set the logic state for.
 * @param [in]    : uddtValOfLogic : Desired logic state to set for the GPIO pin.
 * @return        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtSetPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber , MGPIO_uddtPinLogic_t  uddtValOfLogic)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((GPIOx != NULL_PTR))
	{
		if( ((uddtValOfLogic >= MGPIO_LOGIC_LOW) && (uddtValOfLogic <= MGPIO_LOGIC_HIGH)) &&
				((uddtPinNumber >= MGPIO_PIN0) && (uddtPinNumber <= MGPIO_PIN15)))
		{
			if(uddtValOfLogic == MGPIO_LOGIC_HIGH)
			{
				SET_BIT(GPIOx->BSRR,uddtPinNumber);
				ret = UAPI_OK;
			}
			else if(uddtValOfLogic == MGPIO_LOGIC_LOW)
			{
				SET_BIT(GPIOx->BRR,uddtPinNumber);
				ret = UAPI_OK;
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
* @brief         : Toggles the logic state of a specific GPIO pin.
* @param [in]    : GPIOx : Pointer to the GPIO register map for the target port.
* @param [in]    : uddtPinNumber : The pin number to toggle the logic state for.
* @return        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
*=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtTogPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber )
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(GPIOx != NULL_PTR)
	{
		if((uddtPinNumber >= MGPIO_PIN0) && (uddtPinNumber <= MGPIO_PIN15))
		{
			TOG_BIT(GPIOx->ODR , uddtPinNumber);
			ret = UAPI_OK;
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
* @brief         : Locks the configuration of a specific GPIO pin.
* @param [in]    : GPIOx : Pointer to the GPIO register map for the target port.
* @param [in]    : uddtPinNumber : The pin number to lock the configuration for.
* @return        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
*=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtLockPin(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if(GPIOx != NULL_PTR)
	{
		if((uddtPinNumber >= MGPIO_PIN0) && (uddtPinNumber <= MGPIO_PIN15))
		{
			uint8 u8TempOfReg;
			SET_BIT(GPIOx->LCKR , uddtPinNumber);
			CLR_BIT(GPIOx->LCKR , uddtPinNumber);
			SET_BIT(GPIOx->LCKR , uddtPinNumber);
			u8TempOfReg = GET_BIT(GPIOx->LCKR , uddtPinNumber);
			u8TempOfReg = GET_BIT(GPIOx->LCKR , uddtPinNumber);

			if(u8TempOfReg == MGPIO_IS_LOCKED)
			{
				ret = UAPI_OK;
			}
			else
			{
				ret = UAPI_NOK;
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
* @brief         : Checks if the configuration of a specific GPIO pin is locked.
* @param [in]    : GPIOx : Pointer to the GPIO register map for the target port.
* @param [in]    : uddtPinNumber : The pin number to check for lock status.
* @param [out]   : uddtRetOfLock : Pointer to store the lock status of the GPIO pin.
* @return        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
*=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtIsPinLock(GPIO_registerMap_t  *GPIOx , MGPIO_uddtPinNumber_t uddtPinNumber , MGPIO_uddtPinLock_t *uddtRetOfLock)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if((GPIOx != NULL_PTR) && (uddtRetOfLock != NULL_PTR))
	{
		if((uddtPinNumber >= MGPIO_PIN0) && (uddtPinNumber <= MGPIO_PIN15))
		{
			uint8 u8TempOfReg;
			u8TempOfReg = GET_BIT(GPIOx->LCKR , uddtPinNumber);

			if(u8TempOfReg == MGPIO_IS_LOCKED)
			{
				*uddtRetOfLock = MGPIO_IS_LOCKED;
				ret = UAPI_OK;
			}
			else if(u8TempOfReg == MGPIO_NOT_LOCKED)
			{
				*uddtRetOfLock = MGPIO_NOT_LOCKED;
				ret = UAPI_OK;
			}
			else
			{
				ret = UAPI_NOK;
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
 * @brief         : Retrieves the logic state of the entire GPIO port specified.
 * @param [in]    : GPIOx : Pointer to the GPIO register map for the target port.
 * @param [out]   : u16RetOfLogic : Pointer to store the logic state of the GPIO port.
 * @return        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtGetPort(GPIO_registerMap_t *GPIOx, uint16 *u16RetOfLogic)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if( (GPIOx != NULL_PTR) && (u16RetOfLogic != NULL_PTR))
	{
		*u16RetOfLogic = (uint16)GPIOx->ODR ;
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**=============================================================================
 * @brief         : Sets the logic state of the entire GPIO port specified.
 * @param [in]    : GPIOx : Pointer to the GPIO register map for the target port.
 * @param [in]    : u16ValOfLogic : Desired logic state to set for the GPIO port.
 * @return        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *=============================================================================**/
COMMON_uddtApiState_t MGPIO_uddtSetPort(GPIO_registerMap_t *GPIOx, uint16 u16ValOfLogic)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if( (GPIOx != NULL_PTR))
	{
		GPIOx->ODR = (uint32)u16ValOfLogic;
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

/**==========================================================================================================
 * @Function Name : MGPIO_uddtResetPort
 * @Brief         : Resets : the entire GPIO port specified by resetting the GPIO register map.
 * @Param [in]    : GPIOx : Pointer to the GPIO register map to be reset.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
 *===========================================================================================================**/
COMMON_uddtApiState_t MGPIO_uddtResetPort(GPIO_registerMap_t *GPIOx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if( (GPIOx != NULL_PTR))
	{

	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}


/*________________________________________________________________________________________*/





