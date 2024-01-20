/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : NVIC.c
// Date          : Jan 16, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/


#include "NVIC.h"

/*=============================================================================================
 * @Function Name : MNVIC_uddtEnableIRQ
 * @Brief         : Enables a specific IRQ.
 * @Param [in]    : u8IRQ : IRQ number to be enabled.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtEnableIRQ(uint8 u8IRQ)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if( (u8IRQ >= MNVIC_WWDG_IRQ) && (u8IRQ <= MNVIC_DMA2_Channel4_5_IRQ) )
	{
		NVIC->ISERx[getIRQReg(u8IRQ)] = (1UL << getIRQPos(u8IRQ));
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MNVIC_uddtDisableIRQ
 * @Brief         : Disables a specific IRQ.
 * @Param [in]    : u8IRQ : IRQ number to be disabled.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtDisableIRQ(uint8 u8IRQ)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if( (u8IRQ >= MNVIC_WWDG_IRQ) && (u8IRQ <= MNVIC_DMA2_Channel4_5_IRQ) )
	{
		NVIC->ICERx[getIRQReg(u8IRQ)] = (1UL << getIRQPos(u8IRQ));
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}
	return ret;
}

/*=============================================================================================
 * @Function Name : MNVIC_uddtGetPendingIRQ
 * @Brief         : Gets the pending status of a specific IRQ.
 * @Param [in]    : u8IRQ : IRQ number to check for pending status.
 * @Param [out]   : u8RetOfStatus : Pointer to store the status of the IRQ (1 if pending, 0 if not).
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtGetPendingIRQ(uint8 u8IRQ , uint8 *u8RetOfStatus)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(u8RetOfStatus != NULL_PTR)
	{
		if( (u8IRQ >= MNVIC_WWDG_IRQ) && (u8IRQ <= MNVIC_DMA2_Channel4_5_IRQ) )
		{
			*u8RetOfStatus = ( (NVIC->ISPRx[getIRQReg(u8IRQ)] >> getIRQPos(u8IRQ)) & 0x01);
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

/*=============================================================================================
 * @Function Name : MNVIC_uddtSetPendingIRQ
 * @Brief         : Sets the pending status of a specific IRQ.
 * @Param [in]    : u8IRQ : IRQ number to set as pending.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtSetPendingIRQ(uint8 u8IRQ)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if( (u8IRQ >= MNVIC_WWDG_IRQ) && (u8IRQ <= MNVIC_DMA2_Channel4_5_IRQ) )
	{
		NVIC->ISPRx[getIRQReg(u8IRQ)] = (1UL << getIRQPos(u8IRQ));
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}

	return ret;
}

/*=============================================================================================
 * @Function Name : MNVIC_uddtResetPendingIRQ
 * @Brief         : Resets the pending status of a specific IRQ.
 * @Param [in]    : u8IRQ - IRQ number to reset pending status.
 * @Retval        : COMMON_uddtApiState_t - Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtResetPendingIRQ(uint8 u8IRQ)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if( (u8IRQ >= MNVIC_WWDG_IRQ) && (u8IRQ <= MNVIC_DMA2_Channel4_5_IRQ) )
	{
		NVIC->ICPRx[getIRQReg(u8IRQ)] = (1UL << getIRQPos(u8IRQ));
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}

	return ret;
}

/*=============================================================================================
 * @Function Name : MNVIC_uddtIsActiveIRQ
 * @Brief         : Checks if a specific IRQ is active.
 * @Param [in]    : u8IRQ : IRQ number to check for activity.
 * @Param [out]   : u8RetOfStatus : Pointer to store the status of the IRQ (1 if active, 0 if not).
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtIsActiveIRQ(uint8 u8IRQ, uint8 *u8RetOfStatus)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if(u8RetOfStatus != NULL_PTR)
	{
		if( (u8IRQ >= MNVIC_WWDG_IRQ) && (u8IRQ <= MNVIC_DMA2_Channel4_5_IRQ) )
		{
			*u8RetOfStatus = ( (NVIC->IABRx[getIRQReg(u8IRQ)] >> getIRQPos(u8IRQ)) & 0x01);
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

/*=============================================================================================
 * @Function Name : MNVIC_uddtSetIRQPriority
 * @Brief         : Sets the priority of a specific IRQ.
 * @Param [in]    : u8IRQ : IRQ number to set the priority.
 * @Param [in]    : uddtGroupSelection : Grouping selection for priority configuration.
 * @Param [in]    : u8GroupPriority : Group priority value.
 * @Param [in]    : u8SubPriority : Sub-priority value.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtSetIRQPriority(uint8 u8IRQ, MNVIC_uddtGroups_t uddtGroupSelection, uint8 u8GroupPriority, uint8 u8SubPriority)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if( (u8IRQ >= MNVIC_WWDG_IRQ) && (u8IRQ <= MNVIC_DMA2_Channel4_5_IRQ) )
	{
		if( (uddtGroupSelection >= MNVIC_GP_16_SP_00) && (uddtGroupSelection <= MNVIC_GP_00_SP_16) )
		{
			uint8 u8Priority = 0;
			switch(uddtGroupSelection)
			{
			case MNVIC_GP_00_SP_16 :  u8Priority = u8SubPriority;  break ;
			case MNVIC_GP_16_SP_00 :  u8Priority = u8GroupPriority;  break ;
			case MNVIC_GP_04_SP_04 :  u8Priority = (u8GroupPriority<<2) | u8SubPriority;  break ;
			case MNVIC_GP_02_SP_08 :  u8Priority = (u8GroupPriority<<3) | u8SubPriority;  break ;
			case MNVIC_GP_08_SP_02 :  u8Priority = (u8GroupPriority<<1) | u8SubPriority;  break ;
			}

			NVIC->IPRx[u8IRQ] = (u8Priority<<4) ;
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
	return ret;
}

/*=============================================================================================
 * @Function Name : MNVIC_uddtSetIRQGroup
 * @Brief         : Sets the grouping configuration for priority.
 * @Param [in]    : uddtGroupSelection : Grouping selection for priority configuration.
 * @Retval        : COMMON_uddtApiState_t : Returns the state of the API (see common files for details).
===============================================================================================*/
COMMON_uddtApiState_t MNVIC_uddtSetIRQGroup(MNVIC_uddtGroups_t uddtGroupSelection)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;
	if( (uddtGroupSelection >= MNVIC_GP_16_SP_00) && (uddtGroupSelection <= MNVIC_GP_00_SP_16) )
	{
		SCB->AIRCR = SCB_VECTKEY;
		SCB->AIRCR = SCB_VECTKEY|(uddtGroupSelection<<8);
		ret = UAPI_OK;
	}
	else
	{
		ret = UAPI_INVALID_PARM;
	}

	return ret;
}
