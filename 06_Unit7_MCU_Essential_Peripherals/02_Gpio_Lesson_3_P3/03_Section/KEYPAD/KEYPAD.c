/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : KEYPAD.c
// Date          : Jan 8, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "KEYPAD.h"

static uint8 HKP_arrBtnVal[HKP_ROWS_SIZE][HKP_COLUMNS_SIZE] =
{
		{'7', '8', '9', '/'},
		{'4', '5', '6', '*'},
		{'1', '2', '3', '-'},
		{'#', '0', '=', '+'},
};

COMMON_uddtApiState_t HKP_uddtInit(HKP_uddtCfg_t *KEYPADx)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if (KEYPADx != NULL_PTR)
	{
		uint8 Rowscounter, Colscounter;

		GPIO_uddtPinConfig_t uddtTempPin;

		uddtTempPin.uddtPinLogic = MGPIO_LOGIC_HIGH;
		uddtTempPin.uddtPinMode = MGPIO_OUTPUT_PP_MODE;
		uddtTempPin.uddtPinSpeed = MGPIO_10MHZ_SPEED;

		for (Rowscounter = HKP_LOOP_STARTING_VALUE;Rowscounter < HKP_ROWS_SIZE;Rowscounter++)
		{
			uddtTempPin.GPIOx = KEYPADx->uddtRowsPorts[Rowscounter];
			uddtTempPin.uddtPinNumber = KEYPADx->uddtRowsPins[Rowscounter];
			ret = MGPIO_uddtInitPin(&uddtTempPin);
			if (ret != UAPI_OK) return ret;
		}
		uddtTempPin.uddtPinMode = MGPIO_INPUT_PU_MODE;
		for (Colscounter = HKP_LOOP_STARTING_VALUE;Colscounter < HKP_COLUMNS_SIZE;Colscounter++)
		{
			uddtTempPin.GPIOx = KEYPADx->uddtColumnsPorts[Colscounter];
			uddtTempPin.uddtPinNumber = KEYPADx->uddtColumnsPins[Colscounter];
			ret = MGPIO_uddtInitPin(&uddtTempPin);
			if (ret != UAPI_OK) return ret;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}

COMMON_uddtApiState_t HKP_uddtGetPressedBtn(HKP_uddtCfg_t *KEYPADx , uint8_t *pressedBtnVal)
{
	COMMON_uddtApiState_t ret = UAPI_NOK;

	if ((KEYPADx != NULL_PTR) && (pressedBtnVal != NULL_PTR))
	{
		uint8 Rowscounter, Colscounter;
		MGPIO_uddtPinLogic_t valOfPressedBtn;

		for (Rowscounter = HKP_LOOP_STARTING_VALUE;Rowscounter<HKP_ROWS_SIZE;Rowscounter++) {

			ret = MGPIO_uddtSetPin((KEYPADx->uddtRowsPorts[Rowscounter]),
					(KEYPADx->uddtRowsPins[Rowscounter]),MGPIO_LOGIC_LOW);
			if (ret != UAPI_OK) return ret;

			for (Colscounter = HKP_LOOP_STARTING_VALUE;Colscounter<HKP_COLUMNS_SIZE;Colscounter++) {

				ret = MGPIO_uddtGetPin((KEYPADx->uddtColumnsPorts[Colscounter]),
						(KEYPADx->uddtColumnsPins[Colscounter]),&valOfPressedBtn);
				if (ret != UAPI_OK) return ret;

				if (valOfPressedBtn == MGPIO_LOGIC_LOW)
				{
					while(valOfPressedBtn == MGPIO_LOGIC_LOW)
					{
						ret = MGPIO_uddtGetPin((KEYPADx->uddtColumnsPorts[Colscounter]),
								(KEYPADx->uddtColumnsPins[Colscounter]),&valOfPressedBtn);
						if (ret != UAPI_OK) return ret;
					}
					*pressedBtnVal = HKP_arrBtnVal[Rowscounter][Colscounter];
					break;
				}
			}
			ret = MGPIO_uddtSetPin((KEYPADx->uddtRowsPorts[Rowscounter]),
					(KEYPADx->uddtRowsPins[Rowscounter]),MGPIO_LOGIC_HIGH);
			if (ret != UAPI_OK) return ret;
		}
	}
	else
	{
		ret = UAPI_NULL_PTR;
	}
	return ret;
}
